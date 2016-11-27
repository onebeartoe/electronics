
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.rpi.rgb.led.matrix.RaspberryPiRgbLedMatrix;
import static org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet.LED_MATRIX_HAT_CONTEXT_KEY;

/**
 * @author Roberto Marquez
 */
@WebServlet(name = "FilesystemServet", urlPatterns = {"/files/*"})
public class FilesystemServlet extends HttpServlet
{
    protected Logger logger;
    
    protected RaspberryPiRgbLedMatrix ledMatrixHat;
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        String pi = request.getPathInfo();
        String pathInfo = pi.substring(1); // remove the slash character

        String path = parsePath(pathInfo);
        
        if( !path.startsWith(StillImagesServlet.stillImagesPath)
                || !path.startsWith(AnimationsServlet.animationsPath))
        {
            // The path is not user the current still images or animations directories.
            throw new ServletException("An invalid path was found: " + path);
        }
        else
        {
            // it is a (safe) path under the user defined directories
            File targetFile = new File(path);
            Path animation = targetFile.toPath();

            response.setContentType("image/png");

            OutputStream os = response.getOutputStream();
            Files.copy(animation, os);
            os.flush();
            os.close();
        }
    }

    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());
        
        ServletContext servletContext = getServletContext();
        ledMatrixHat = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);    
    }
    
    private String parsePath(String pathInfo) throws ServletException
    {
        final String animations = "animations";
        final String stillImages = "still-images";
        
        int namePosition = pathInfo.lastIndexOf("/") + 1;
        String name = pathInfo.substring(namePosition);
        
        String path;
        
        if(pathInfo.contains(animations + "/"))
        {
            path = AnimationsServlet.animationsPath + name;
        }
        else if( pathInfo.contains(stillImages + "/") )
        {
            path = StillImagesServlet.stillImagesPath + name;
        }
        else
        {
            throw new ServletException("Parsing expects either animations or still images");
        }
        
        return path;
    }
}
