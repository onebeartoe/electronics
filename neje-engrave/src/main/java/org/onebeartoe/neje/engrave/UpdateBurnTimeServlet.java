
package org.onebeartoe.neje.engrave;

import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet class handles requests to update the laser engraver's burn 
 * time value.
 * 
 * @author Roberto Marquez
 * 
 */
@WebServlet(urlPatterns = {"/engraver/burn-time/*"})
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
        String pathInfo = request.getPathInfo();
        
        final long defaultBurnTime = 15L;
        
        long burnTime = defaultBurnTime;
        
        try
        {
            String s = pathInfo.substring(1);

            burnTime = Long.parseLong(s);
        }
        catch(Exception e)
        {
            logger.warning("error parsing burn time: " + e.getMessage() );
        }
        
        String message = "The request for updating the burn time to " + burnTime + " is being processed.";

        logger.info(message);
        
        ServletContext servletContext = getServletContext();
        
        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        NejeEngraver engraver = applicationProfile.getEngraver();
                
        long maxBurnTime = 60;
        
        if( 0 < burnTime && burnTime < maxBurnTime)
        {
            engraver.setBurnTime(burnTime);
        }
        else
        {
            engraver.setBurnTime(15L);
            
            message += "  Cannot use invalid burn time value of " + burnTime;
        }
        
        return message;
    }
}
