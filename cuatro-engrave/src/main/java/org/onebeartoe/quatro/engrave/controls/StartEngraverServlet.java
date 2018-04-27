
package org.onebeartoe.quatro.engrave.controls;

import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
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
import org.onebeartoe.quatro.engrave.filesystem.FilesystemValidationService;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 *
 * This servlet adds a NejeEgraver object to the servlet context.
 */
@WebServlet(urlPatterns = {"/engraver/start"}, loadOnStartup = 1)
public class StartEngraverServlet extends PlainTextResponseServlet
{
    private Logger logger;
    
    public static final String APPLICTION_PROFILE_CONTEXT_KEY = "APPLICTION_PROFILE_CONTEXT_KEY";
    
    private NejeEngraver engraver;
    
    private ApplicationProfile applicationProfile;
    
    private final String  BASE_SUB_DIRECTORY = "/.config/neje-graver/uploads/";    
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String result = "status is all good";
        
        try
        {
            engraver.startEngraving();
        } 
        catch (IOException ex)
        {
            result = "An error occured while starting the engraving: " + ex.getMessage();
            
            logger.severe(result);
        }                
                
        return result;
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

            FilesystemValidationService service = new FilesystemValidationService();
            
            applicationProfile.setFilesystemValidationService(service);
            
            applicationProfile.setEngraver(engraver);

            servletContext.setAttribute(APPLICTION_PROFILE_CONTEXT_KEY, applicationProfile);
        }
    }    
}
