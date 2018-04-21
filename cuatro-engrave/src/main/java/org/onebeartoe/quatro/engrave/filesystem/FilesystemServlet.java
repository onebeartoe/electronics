/*
 */
package org.onebeartoe.quatro.engrave.filesystem;

import java.io.File;
import java.io.IOException;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import static org.onebeartoe.quatro.engrave.controls.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet handles requests for filesystem listings.
 */
@WebServlet(urlPatterns = {"/filesystem/*"})
public class FilesystemServlet extends PlainTextResponseServlet
{    
    protected Logger logger;
    
    private FilesystemValidationService filesystemValidationService;
    
    private ApplicationProfile applicationProfile;
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String subpath = request.getPathInfo();
        
        StringBuilder responseText = new StringBuilder("path infos: " + subpath);
        
        String [] files = null;
        
        File baseDir = applicationProfile.getBaseDirectory();

        File directory = new File(baseDir, subpath);
        
        try
        {
            filesystemValidationService.validatePath(baseDir, subpath);        

            logger.info("directory: " + directory.getAbsolutePath() );

            files = directory.list();
            
        }
        catch(IllegalArgumentException ex)
        {
            
            
            ex.printStackTrace();
        }        
                        
        if(files == null)
        {
            responseText.append("<br/>");
            responseText.append("no files are present: " + directory.getAbsolutePath() );
        }
        else
        {
            for(String f : files)
            {
                responseText.append("<br/>");
                responseText.append(f);
                responseText.append("<br/>");
            }
        }
        
        return responseText.toString();
    }
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());

        ServletContext servletContext = getServletContext();
        
        applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        filesystemValidationService = applicationProfile.getFilesystemValidationService();
    }
}
