
package org.onebeartoe.quatro.engrave.controls;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author Roberto Marquez
 */
@WebServlet(urlPatterns = {"/controls/reset/*"})
public class ResetEgraverServlet extends HttpServlet
{
    protected Logger logger;
    
    public ResetEgraverServlet()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException            
    {
        String pi = request.getPathInfo();
//        String animationName = pi.substring(1); // remove the slash character

        logger.log(Level.INFO, "sending initial data to user..");
        StringBuilder sb = new StringBuilder("request recieved");

        try 
        {
            //TODO: send a message to the egraver object
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

        OutputStream os = response.getOutputStream();
        PrintWriter pw = new PrintWriter(os);
        
        pw.print( sb.toString() );
        pw.flush();
        pw.close();
    }
}
