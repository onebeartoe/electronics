
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
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import org.onebeartoe.quatro.engrave.NejeEngraver;
import static org.onebeartoe.quatro.engrave.controls.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;

/**
 * @author Roberto Marquez
 */
@WebServlet(urlPatterns = {"/engraver/reset/*"})
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
        
        StringBuilder sb = new StringBuilder("sending initial data to user..");
        logger.info( sb.toString() );
        try 
        {
            engraver.reset();
        } 
        catch (Exception ex) 
        {
            sb.append("Error: " + ex.getMessage() );
            sb.append("<br/><br/>");
            
            logger.log(Level.SEVERE, sb.toString(), ex);
        }

        sb.append("request processed");
        
        logger.log(Level.INFO, sb.toString());

        sb.append("<br/><br/>");

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
        
        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        engraver = applicationProfile.getEngraver();
    }   
}
