
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
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import org.onebeartoe.quatro.engrave.NejeEngraver;
import org.onebeartoe.quatro.engrave.filesystem.FilesystemValidationService;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 *
 * This servlet adds a NejeEgraver object to the servlet context.
 * 
 */
@WebServlet(urlPatterns = {"/engraver/start"}, loadOnStartup = 1)
public class StartEngraverServlet extends PlainTextResponseServlet
{
    private Logger logger;
    
    public static final String APPLICTION_PROFILE_CONTEXT_KEY = "APPLICTION_PROFILE_CONTEXT_KEY";
    
//    private static NejeEngraver engraver;
    
    private ApplicationProfile applicationProfile;
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String result = "The Start messge was sent to engraver.";
     
        NejeEngraver engraver = applicationProfile.getEngraver();
        
        try
        {
            String burnTime = "14";
            
            engraver.startEngraving(burnTime);
        } 
        catch (IOException ex)
        {
            result = "An error occured while starting the engraving: " + ex.getMessage();
            
            logger.severe(result);
        }                
                
        return result;
    }

    private NejeEngraver defaultSettings()
    {
        NejeEngraver engraver = new NejeEngraver();

        String ezGraverCliPath = "/opt/ez-graver/EzGraverCli/EzGraverCli";
//        String ezGraverCliPath = "/home/roberto/Versioning/group/github/camrein/EzGraver-unix_cli_fixes/EzGraverCli/EzGraverCli";
        
        engraver.setCliExecutable(ezGraverCliPath);
        
        return engraver;
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
            loadApplicationProfile();
        }

        servletContext.setAttribute(APPLICTION_PROFILE_CONTEXT_KEY, applicationProfile);        
    }

    /**
     * this method load the application properties for the entire application.
     * @throws FileNotFoundException 
     */
    private void loadApplicationProfile()
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
        catch (FileNotFoundException ex)
        {
            String message = ex.getMessage();
            
            logger.severe(message);
        }
        
        if(engraver == null)
        {
            engraver = defaultSettings();
        }
                
        applicationProfile = new ApplicationProfile();

        applicationProfile.setBaseDirectory(baseDir);

        boolean mkdirs = baseDir.mkdirs();
        logger.info("basedDir: " + baseDir.getAbsolutePath() + " created: " + mkdirs);
                                    
        FilesystemValidationService service = new FilesystemValidationService();

        applicationProfile.setFilesystemValidationService(service);

        applicationProfile.setEngraver(engraver);
    }
}
