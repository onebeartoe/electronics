
package org.onebeartoe.quatro.engrave.controls;

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
 * This servlet handles requests to pause the laser engraver.
 */
@WebServlet(urlPatterns = {"/engraver/pause"})
public class PauseEgraverServlet extends PlainTextResponseServlet
{
    private Logger logger;
    
    private NejeEngraver engraver;
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String result = "The engraver was paused.";
        
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
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());                
        
        ServletContext servletContext = getServletContext();

        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        engraver = applicationProfile.getEngraver();
    }    
}
