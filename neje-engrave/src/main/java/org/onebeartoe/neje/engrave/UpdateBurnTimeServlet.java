
package org.onebeartoe.neje.engrave;

import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import org.onebeartoe.quatro.engrave.NejeEngraver;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet class handles requests to update the laser engraver's burn 
 * time value.
 * 
 * @author Roberto Marquez
 * 
 */
@WebServlet(urlPatterns = {"/engraver/burn-time"})
public class UpdateBurnTimeServlet extends PlainTextResponseServlet
{
    private Logger logger;
    
    public UpdateBurnTimeServlet()
    {
        String className = getClass().getName();
        
        logger = Logger.getLogger(className);
    }

    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        logger.info("The request for updating the burn time to " + "UPDATE-THIS" + " is being processed.");
        
        ServletContext servletContext = getServletContext();
        
        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        NejeEngraver engraver = applicationProfile.getEngraver();
                
        engraver.setBurnTime(15L);
        
        return "this is the respose form burn time";
    }
    
}
