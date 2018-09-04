
package org.onebeartoe.neje.engrave;

import java.io.IOException;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet handles requests to pause the laser engraver.
 */
@WebServlet(urlPatterns = {"/engraver/pause"})
public class PauseEgraverServlet extends PlainTextResponseServlet
{
    private final Logger logger;

    public PauseEgraverServlet()
    {
        logger = Logger.getLogger(getClass().getName());                
    }
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String result = "The engraver was paused.";
        
        ServletContext servletContext = getServletContext();

        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
                
        NejeEngraver engraver = applicationProfile.getEngraver();
        
        try
        {
            engraver.pause();
            
        } 
        catch (IOException ex)
        {
            logger.severe( ex.getMessage() );
        }
        
        return result;
    }
}
