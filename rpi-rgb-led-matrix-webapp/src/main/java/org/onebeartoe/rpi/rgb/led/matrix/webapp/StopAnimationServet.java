
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.util.logging.Level;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(name = "StopAnimationServet", urlPatterns = {"/ploop/*"})
public class StopAnimationServet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response) 
    {
        StringBuilder sb = new StringBuilder();
        
        try 
        {
            sb.append("<br/>");
            sb.append("stop request received");
            ledMatrixHat.stopCommand();
        } 
        catch (InterruptedException ex) 
        {
            String message = "error: " + ex.getMessage();
        
            sb.append("<br/>");
            sb.append(message);
            logger.log(Level.SEVERE, message, ex);
        }
        
        sb.append("<br/>");
        sb.append("stop request processed");
        
        return sb.toString();
    }
}
