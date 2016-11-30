
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
 * The loadOnStartup is present to ensure the ledMatrix object is created before
 * referenced.
 * 
 * @author Roberto Marquez
 * 
 */
@WebServlet(name = "FilesystemServet", urlPatterns = {"/files/*"}, loadOnStartup = 1)
public class FilesystemServlet extends RaspberryPiRgbLedMatrixServlet
{
    protected Logger logger;
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        String pi = request.getPathInfo();
        String pathInfo = pi.substring(1); // remove the slash character

        ParseInfo info = parsePath(pathInfo);
        
        String stillImagesTarget = (new File(ledMatrix.getStillImagesPath())).getAbsolutePath();
        String animationsTarget = (new File(ledMatrix.getAnimationsPath() )).getAbsolutePath();
        
        // "security", should this logic be inverted to only....
        if( (info.type == ParseType.IMAGE && !info.path.startsWith(stillImagesTarget) )
                || 
            (info.type ==ParseType.ANIMATION && !info.path.startsWith(animationsTarget) )
        )
        {
            // The path is not user the current still images or animations directories.
            String message = "An invalid path was found: " + info.path + " ---- expected: " + stillImagesTarget
                             + " or " + animationsTarget;
            
            throw new ServletException(message);
        }
        else
        {
            // it is a (safe) path under the user defined directories
            File targetFile = new File(info.path);
            Path animation = targetFile.toPath();

            //TODO: set the correct content type for the PNG and GIF animations
            response.setContentType("image/png");

            OutputStream os = response.getOutputStream();
            Files.copy(animation, os);
            os.flush();
            os.close();
        }
    }
    
    private ParseInfo parsePath(String pathInfo) throws ServletException
    {
        final String animations = "animations";
        final String stillImages = "still-images";
        
        int namePosition = pathInfo.lastIndexOf("/") + 1;
        String name = pathInfo.substring(namePosition);
        
        String path;
        ParseInfo info = new ParseInfo();
        info.type = ParseType.UNKNOWN;
        
        if(pathInfo.contains(animations + "/"))
        {
            path = ledMatrix.getAnimationsPath() + name;
            info.type = ParseType.ANIMATION;
        }
        else if( pathInfo.contains(stillImages + "/") )
        {
            path = ledMatrix.getStillImagesPath() + name;
            info.type = ParseType.IMAGE;
        }
        else
        {
            throw new ServletException("Parsing expects either animations or still images");
        }
        
        // remove MS Windows crap
        File f = new File(path);
        path = f.getAbsolutePath();
        
        info.path = path;
        
        return info;
    }
    
    private class ParseInfo
    {
        String path;
        
        ParseType type;
    }
    
    private enum ParseType
    {
        IMAGE,
        ANIMATION,
        UNKNOWN
    }
}
