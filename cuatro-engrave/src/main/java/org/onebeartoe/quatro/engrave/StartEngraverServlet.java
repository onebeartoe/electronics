
package org.onebeartoe.quatro.engrave;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * This servlet adds a NejeEgraver object to the servlet context.
 */
@WebServlet(urlPatterns = {"/controls/start"}, loadOnStartup = 1)
public class StartEngraverServlet extends HttpServlet
{
    private Logger logger;
    
    public static final String ENGRAVER_CONTEXT_KEY = "ENGRAVER_CONTEXT_KEY";
    
    private NejeEngraver engraver;
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        engraver.startEngraving();
        
        request.setAttribute("status", "status is all good");
                
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/controls/index.jsp");
        rd.forward(request, response);
    }
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());                
        
        ServletContext servletContext = getServletContext();
        
        engraver = (NejeEngraver) servletContext.getAttribute(ENGRAVER_CONTEXT_KEY);
        
        if(engraver == null)
        {
            engraver = new NejeEngraver();
            
            servletContext.setAttribute(ENGRAVER_CONTEXT_KEY, engraver);
        }
    }    
}
