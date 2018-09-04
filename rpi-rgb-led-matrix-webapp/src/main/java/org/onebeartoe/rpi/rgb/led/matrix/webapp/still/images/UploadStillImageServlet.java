
package org.onebeartoe.rpi.rgb.led.matrix.webapp.still.images;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

/**
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(name = "UploadStillImageServlet", urlPatterns = {"/still-images/upload"})
@MultipartConfig
public class UploadStillImageServlet extends StillImagesServlet
{
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse responseee)
    {
        Part filePart = null;
        
        try
        {
            filePart = request.getPart("still-image");
        } 
        catch (IOException | ServletException ex)
        {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }

        String message = "--message not set--";
        
        if(filePart != null)
        {
            final String fileName = getFileName(filePart);

            String outpath = ledMatrix.getStillImagesPath() + fileName;
            File outfile = new File(outpath);

            try (OutputStream out = new FileOutputStream(outfile);
                 InputStream filecontent = filePart.getInputStream();)
            {
                int read = 0;
                final byte[] bytes = new byte[1024];

                while ((read = filecontent.read(bytes)) != -1) 
                {
                    out.write(bytes, 0, read);
                }
                message += "New file " + fileName + " created at " + outpath;
                logger.log(Level.INFO, message);
                logger.log(Level.INFO, "File{0}being uploaded to {1}", 
                        new Object[]{fileName, outpath});
            } 
            catch (IOException fne) 
            {
                StringBuilder sb = new StringBuilder();
                sb.append("You either did not specify a file to upload or are "
                        + "trying to upload a file to a protected or nonexistent "
                        + "location.");

                sb.append("\n<br/> ERROR: " + fne.getMessage());

                sb.append("Problems during file upload. Error: " + fne.getMessage());

                message += sb.toString();
                logger.log(Level.SEVERE, message);
            }
        }
    
        request.setAttribute("responseMessages", message);
    
        doResponse(request, responseee);
    }

    private String getFileName(final Part part) 
    {
        final String partHeader = part.getHeader("content-disposition");
        logger.log(Level.INFO, "Part Header = {0}", partHeader);
        for (String content : part.getHeader("content-disposition").split(";")) 
        {
            if (content.trim().startsWith("filename")) 
            {
                return content.substring(
                        content.indexOf('=') + 1).trim().replace("\"", "");
            }
        }
        return null;
    }    
}
