
package org.onebeartoe.rpi.rgb.led.matrix.webapp.animations;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.logging.Level;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(name = "StopAnimationServet", urlPatterns = {"/ploop/*"})
public class StopAnimationServet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        StringBuilder sb = new StringBuilder();
        
        try 
        {
            sb.append("<br/>");
            sb.append("stop request received");
            ledMatrix.stopCommand();
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
        
        OutputStream os = response.getOutputStream();
        PrintWriter pw = new PrintWriter(os);
        pw.print( sb.toString() );
        pw.flush();
        pw.close();
    }
}
