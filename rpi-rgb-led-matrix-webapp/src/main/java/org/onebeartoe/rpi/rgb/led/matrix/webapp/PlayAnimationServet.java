
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.util.logging.Level;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 * 
 * An instance of this servlet is created on startup to ensure a Camera object 
 * is always an attribute in the ServletContext for the application.
 * 
 */
@WebServlet(name = "PlayAnimationServet", urlPatterns = {"/animation/play/*"}, loadOnStartup = 1)
public class PlayAnimationServet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response) 
    {
        String pi = request.getPathInfo();
        String animationName = pi.substring(1); // remove the slash character

        logger.log(Level.INFO, "sending initial data to user..");
        StringBuilder sb = new StringBuilder("request recieved");

        try 
        {
            String gifPath = AnimationsServlet.animationsPath + animationName;
            ledMatrixHat.stopCommand();
            ledMatrixHat.startAnimationCommand(gifPath);
        } 
        catch (Exception ex) 
        {
            String message = "Error: " + ex.getMessage();
            sb.append("<br/><br/>" + message);
            logger.log(Level.SEVERE, message, ex);
        }

        String message = "request processed";
        logger.log(Level.INFO, message);

        String r = "<br/><br/>" + message;

        sb.append(r);

        return sb.toString();
    }    
}
