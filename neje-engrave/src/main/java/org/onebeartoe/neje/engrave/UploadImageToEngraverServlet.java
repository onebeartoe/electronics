
package org.onebeartoe.neje.engrave;

import java.io.File;
import java.io.IOException;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.neje.engrave.filesystem.FilesystemValidationService;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet handles requests to send an image to the Neje Engraver.
 */
@WebServlet(urlPatterns = {"/engraver/upload-image/*"})
public class UploadImageToEngraverServlet extends PlainTextResponseServlet
{
    private final Logger logger;

//TODO:    add a org.onebeartoe.neje.engrave.filesystem.FilesystemValidationService instance member 
    FilesystemValidationService validationService;
    
    public UploadImageToEngraverServlet()
    {
        logger = Logger.getLogger(getClass().getName());
        
        validationService = new FilesystemValidationService();
    }

    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String subpath = request.getPathInfo();
        
        String result = "The upload message was sent to the engraver for " + subpath + ".";
  
        ServletContext servletContext = getServletContext();
        
        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        File baseDir = applicationProfile.getBaseDirectory();
        
        String safeSubpath = validationService.validateAndSanitize(baseDir, subpath);
        
        File imageUpload = new File(baseDir, safeSubpath);
        
        try
        {
            NejeEngraver engraver = applicationProfile.getEngraver();
            
            engraver.uploadImage(imageUpload);
        } 
        catch (IOException ex)
        {
            result = "error loading " 
                     + imageUpload.getAbsolutePath()
                     + " - "
                     + ex.getMessage();
            
            logger.severe(result);
        }
        
        return result;
    }
}
