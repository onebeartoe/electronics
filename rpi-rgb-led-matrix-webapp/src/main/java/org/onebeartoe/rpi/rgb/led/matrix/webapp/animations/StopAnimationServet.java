
package org.onebeartoe.rpi.rgb.led.matrix.webapp.animations;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet;

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
