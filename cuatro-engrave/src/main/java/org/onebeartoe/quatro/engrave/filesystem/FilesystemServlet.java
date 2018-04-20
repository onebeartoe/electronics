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
    
    private ApplicationProfile applicationProfile;
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String subpath = request.getPathInfo();
        
        validatePath(subpath);

        String responseText = "path infos: " + subpath;

        File baseDir = applicationProfile.getBaseDirectory();
        
        File directory = new File(baseDir, subpath);
        
        logger.info("directory: " + directory.getAbsolutePath() );
        
        String [] files = directory.list();
        
        if(files == null)
        {
            responseText += "<br/>";
            responseText += "no files are present: " + directory.getAbsolutePath();
        }
        else
        {
            for(String f : files)
            {
                responseText += "<br/>";
                responseText += f;
                responseText += "<br/>";
            }
        }
        
        return responseText;
    }
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());

        ServletContext servletContext = getServletContext();
        
        applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
    }
    
    private void validatePath(String path)
    {
        File baseDirectory = applicationProfile.getBaseDirectory();

        String baseAbsolute = baseDirectory.getAbsolutePath();
        
        File suspectPath = new File(baseDirectory, path);
        String suspectAbsolute = suspectPath.getAbsolutePath();
        
        if( !suspectAbsolute.startsWith(baseAbsolute) )
        {
            throw new IllegalArgumentException("bad filesystem path: " + suspectAbsolute);
        }
    }
}
