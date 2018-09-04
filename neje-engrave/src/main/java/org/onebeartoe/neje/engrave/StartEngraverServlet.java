
package org.onebeartoe.neje.engrave;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.io.ObjectRetriever;
import org.onebeartoe.neje.engrave.filesystem.FilesystemValidationService;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 *
 * This servlet adds a NejeEgraver object to the servlet context.
 * 
 */
@WebServlet(urlPatterns = {"/engraver/start"}, loadOnStartup = 1)
public class StartEngraverServlet extends PlainTextResponseServlet
{
    private final Logger logger;
    
    public static final String APPLICTION_PROFILE_CONTEXT_KEY = "APPLICTION_PROFILE_CONTEXT_KEY";
    
    public StartEngraverServlet()
    {
        logger = Logger.getLogger(getClass().getName());        
    }
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String responseMessage = "The start messge was sent to engraver:";
     
        ServletContext servletContext = getServletContext();
        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        NejeEngraver engraver = applicationProfile.getEngraver();
        
        try
        {            
            CommandResult commandResult = engraver.startEngraving();
            
            responseMessage += "<p>" + commandResult.getCommandLine() + "</p>";
        } 
        catch (IOException ex)
        {
            responseMessage = "An error occured while starting the engraving: " + ex.getMessage();
            
            logger.severe(responseMessage);
        }
                
        return responseMessage;
    }

    private NejeEngraver defaultSettings()
    {
        NejeEngraver engraver = new NejeEngraver();

        String ezGraverCliPath = "/opt/ez-graver/EzGraverCli/EzGraverCli";
        
        engraver.setCliExecutable(ezGraverCliPath);
        
        return engraver;
    }
    
    @Override
    public void init() throws ServletException
    {
        super.init();
      
        ServletContext servletContext = getServletContext();

        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        if(applicationProfile == null)
        {
            applicationProfile = loadApplicationProfile();
        }

        servletContext.setAttribute(APPLICTION_PROFILE_CONTEXT_KEY, applicationProfile);        
    }

    /**
     * this method load the application properties for the entire application.
     * @throws FileNotFoundException 
     */
    private ApplicationProfile loadApplicationProfile()
    {
        String homeDir = System.getProperty("user.home");

        File baseDir = new File(homeDir + ApplicationProfile.BASE_SUB_DIRECTORY);

        logger.info("basedDir: " + baseDir.getAbsolutePath() );

        File cliConfigFile = new File(baseDir, ApplicationProfile.CONFIGURATION_FILENAME);
        
        NejeEngraver engraver = null;
        
        try
        {
            engraver = (NejeEngraver) ObjectRetriever.decodeObject(cliConfigFile);
        } 
        catch (Exception ex)
        {
            String message = ex.getMessage();
            
            logger.severe(message);
        }
        
        if(engraver == null)
        {
            engraver = defaultSettings();
        }
                
        ApplicationProfile applicationProfile = new ApplicationProfile();

        applicationProfile.setBaseDirectory(baseDir);

        boolean mkdirs = baseDir.mkdirs();
        
        String message = "basedDir: " + baseDir.getAbsolutePath() + " created: " + mkdirs;

        logger.info(message);
                                    
        FilesystemValidationService service = new FilesystemValidationService();

        applicationProfile.setFilesystemValidationService(service);

        applicationProfile.setEngraver(engraver);
        
        return applicationProfile;
    }
}
              