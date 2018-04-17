
package org.onebeartoe.quatro.engrave.controls;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import static org.onebeartoe.quatro.engrave.controls.StartEngraverServlet.ENGRAVER_CONTEXT_KEY;
import org.onebeartoe.quatro.engrave.NejeEngraver;

/**
 * @author Roberto Marquez
 */
@WebServlet(urlPatterns = {"/controls/reset/*"})
public class ResetEgraverServlet extends HttpServlet
{
    protected Logger logger;
    
    private NejeEngraver engraver;
    
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
            engraver.reset();
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
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());                
        
        ServletContext servletContext = getServletContext();
        
        engraver = (NejeEngraver) servletContext.getAttribute(ENGRAVER_CONTEXT_KEY);
    }   
}
