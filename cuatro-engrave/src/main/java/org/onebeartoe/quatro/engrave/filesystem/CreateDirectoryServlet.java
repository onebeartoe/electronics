
package org.onebeartoe.quatro.engrave.filesystem;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.lang3.StringUtils;
import org.onebeartoe.quatro.engrave.ApplicationProfile;
import static org.onebeartoe.quatro.engrave.controls.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;

/**
 * This servlet handles requests to creates directories under the file listing 
 * base directory.
 */
@WebServlet(urlPatterns = {"/filesystem/create-directory"})
public class CreateDirectoryServlet extends HttpServlet
{
    private Logger logger;
    
    private ApplicationProfile applicationProfile;
    
    private FilesystemValidationService filesystemValidationService;
    
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException 
    {
        String path = request.getParameter("path");
        
        String filesystemLog = null;
        
        if( StringUtils.isEmpty(path) )
        {
            filesystemLog = "No path was specified.";
        }
        else
        {
            filesystemLog = processRequestParameter(path);
        }

        request.setAttribute("filesystemLog", filesystemLog);

        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/controls/index.jsp");
        rd.forward(request, response);
    }
    
    private String processRequestParameter(String path)
    {
        File baseDirectory = applicationProfile.getBaseDirectory();
        
        File directoryToCreate = new File(baseDirectory, path);
        
        String filesystemLog = "The directory was created: " + directoryToCreate.getAbsolutePath();
        
        try
        {
            filesystemValidationService.validatePath(baseDirectory, path);
            
            if( directoryToCreate.exists() )
            {
                filesystemLog = "The file alredy exists: " + directoryToCreate.getAbsolutePath();
            }
            else
            {
                boolean wasCreated = directoryToCreate.mkdirs();

                if(!wasCreated)
                {
                    filesystemLog = "With no error given, the directory was not created; " 
                                    + directoryToCreate.getAbsolutePath();
                }
            }                                    
        }
        catch(IllegalArgumentException ex)
        {
            filesystemLog = "The directory (" 
                            + directoryToCreate.getAbsolutePath() + ") was not created; "
                            + ex.getMessage();
        }

        return filesystemLog;
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
