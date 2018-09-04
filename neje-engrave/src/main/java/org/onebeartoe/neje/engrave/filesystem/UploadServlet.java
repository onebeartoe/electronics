
package org.onebeartoe.neje.engrave.filesystem;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import org.onebeartoe.neje.engrave.ApplicationProfile;

import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;

/**
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(urlPatterns = {"/filesystem/upload"})
@MultipartConfig
public class UploadServlet extends HttpServlet
{
    protected final Logger logger;
  
    public UploadServlet()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        Part filePart = null;
        try
        {
            filePart = request.getPart("upload");
        } 
        catch (IOException | ServletException ex)
        {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }

        String message = null;
        
        if(filePart != null)
        {
            final String fileName = getFileName(filePart);

            ServletContext servletContext = getServletContext();
        
            ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
                    
            File outdir = applicationProfile.getBaseDirectory();
            
            File outfile = new File(outdir, fileName);

            try(OutputStream out = new FileOutputStream(outfile);
                InputStream filecontent = filePart.getInputStream() )
            {
                int read = 0;
                final byte[] bytes = new byte[1024];

                while ((read = filecontent.read(bytes)) != -1) 
                {
                    out.write(bytes, 0, read);
                }

                String outpath = outfile.getAbsolutePath();
                message += "New file " + fileName + " created at " + outpath;
                logger.log(Level.INFO, message);
                logger.log(Level.INFO, "File {0} being uploaded to {1}",  new Object[]{fileName, outpath});
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
        else
        {
            message = "No filePart is available.";
        }

        request.setAttribute("responseMessages", message);
    
        List fileNames = null;
        request.setAttribute("animationNames", fileNames);

        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/controls/index.jsp");
        
        try
        {
            rd.forward(request, response);
        } 
        catch (IOException | ServletException ex)
        {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
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
