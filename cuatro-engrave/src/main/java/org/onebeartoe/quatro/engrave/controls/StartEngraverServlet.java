
package org.onebeartoe.quatro.engrave.controls;

import java.io.File;
import java.io.IOException;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import org.onebeartoe.quatro.engrave.NejeEngraver;

/**
 *
 * This servlet adds a NejeEgraver object to the servlet context.
 */
@WebServlet(urlPatterns = {"/controls/start"}, loadOnStartup = 1)
public class StartEngraverServlet extends HttpServlet
{
    private Logger logger;
    
    public static final String APPLICTION_PROFILE_CONTEXT_KEY = "APPLICTION_PROFILE_CONTEXT_KEY";
    
    private NejeEngraver engraver;
    
    private ApplicationProfile applicationProfile;
    
    private final String  BASE_SUB_DIRECTORY = "/.config/neje-graver/uploads/";    
    
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

        applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        if(applicationProfile == null)
        {
            applicationProfile = new ApplicationProfile();
            
            String homeDir = System.getProperty("user.home");
        
            File baseDir = new File(homeDir + BASE_SUB_DIRECTORY);
            logger.info("basedDir: " + baseDir.getAbsolutePath() );

            applicationProfile.setBaseDirectory(baseDir);
            
            boolean mkdirs = baseDir.mkdirs();
            logger.info("basedDir: " + baseDir.getAbsolutePath() + " created: " + mkdirs);
            
            engraver = new NejeEngraver();
            
            applicationProfile.setEngraver(engraver);

            servletContext.setAttribute(APPLICTION_PROFILE_CONTEXT_KEY, applicationProfile);
        }
    }    
}
