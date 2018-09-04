
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
 */
@WebServlet(name = "StopAnimationServet", urlPatterns = {"/animation/stop/*"})
public class StopAnimationServet extends RaspberryPiRgbLedMatrixServlet
{
    private final String BREAK = "<br/>";
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        StringBuilder sb = new StringBuilder();
        
        try 
        {
            sb.append(BREAK);
            sb.append("stop request received");
            
            ServletContext servletContext = getServletContext();
            RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);        
            
            ledMatrix.stopCommand();
        } 
        catch (InterruptedException ex) 
        {
            String message = "error: " + ex.getMessage();
        
            sb.append(BREAK);
            sb.append(message);
            logger.log(Level.SEVERE, message, ex);
            
            Thread.currentThread().interrupt();
        }
        
        sb.append(BREAK);
        sb.append("stop request processed");

        try(OutputStream os = response.getOutputStream();
            PrintWriter pw = new PrintWriter(os) )
        {
            pw.print( sb.toString() );
            pw.flush();
        } 
        catch (IOException ex)
        {
            logger.log(Level.SEVERE, null, ex);
        }
    }
}
