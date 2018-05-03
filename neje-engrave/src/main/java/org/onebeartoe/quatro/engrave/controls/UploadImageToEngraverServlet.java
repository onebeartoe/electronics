
package org.onebeartoe.quatro.engrave.controls;

import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import org.onebeartoe.quatro.engrave.NejeEngraver;
import static org.onebeartoe.quatro.engrave.controls.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet handles requests to send an image to the Neje Engraver.
 */
@WebServlet(urlPatterns = {"/engraver/upload-image/*"})
public class UploadImageToEngraverServlet extends PlainTextResponseServlet
{
    private Logger logger;
    
    private ApplicationProfile applicationProfile;
    
    private NejeEngraver engraver;
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String subpath = request.getPathInfo();
        
        String result = "The upload message was sent to the engraver for " + subpath + ".";
        
        File baseDir = applicationProfile.getBaseDirectory();
        
        File imageUpload = new File(baseDir, subpath);
        
        try
        {
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
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());

        ServletContext servletContext = getServletContext();
        
        applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        engraver = applicationProfile.getEngraver();
    }
}
