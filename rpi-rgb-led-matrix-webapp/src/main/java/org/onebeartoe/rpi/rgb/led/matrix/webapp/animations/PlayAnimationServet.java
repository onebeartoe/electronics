
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
