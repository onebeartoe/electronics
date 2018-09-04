
package org.onebeartoe.rpi.rgb.led.matrix.webapp.animations;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.logging.Level;
import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.rpi.rgb.led.matrix.RaspberryPiRgbLedMatrix;
import org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet;
import static org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet.LED_MATRIX_HAT_CONTEXT_KEY;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 * 
 */
@WebServlet(name = "PlayAnimationServet", urlPatterns = {"/animation/play/*"})
public class PlayAnimationServet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        String pi = request.getPathInfo();
        String animationName = pi.substring(1); // remove the slash character

        logger.log(Level.INFO, "sending initial data to user..");
        StringBuilder sb = new StringBuilder("request recieved");

        try 
        {
            ServletContext servletContext = getServletContext();
            RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);        
            ledMatrix.stopCommand();
            ledMatrix.startAnimationCommand(animationName);
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
        
        try(OutputStream os = response.getOutputStream();
            PrintWriter pw = new PrintWriter(os) )
        {
            pw.print( sb.toString() );
            pw.flush();
        } 
        catch (IOException ex)
        {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }
}
