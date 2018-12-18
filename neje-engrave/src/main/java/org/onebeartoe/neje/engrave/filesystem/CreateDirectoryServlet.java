
package org.onebeartoe.neje.engrave.filesystem;

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
import org.onebeartoe.neje.engrave.ApplicationProfile;

import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;

/**
 * This servlet handles requests to creates directories under the file listing 
 * base directory.
 */
@WebServlet(urlPatterns = {"/filesystem/create-directory"})
public class CreateDirectoryServlet extends HttpServlet
{
    private final Logger logger;
    
    public CreateDirectoryServlet()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        String path = request.getParameter("path");
    
        String filesystemLog = processRequestParameter(path);

        request.setAttribute("filesystemLog", filesystemLog);

        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/controls/index.jsp");
        try
        {
            rd.forward(request, response);
        } 
        catch (IOException | ServletException ex)
        {
            logger.severe( ex.getMessage() );
        }
    }
    
    private String processRequestParameter(String path)
    {
        ServletContext servletContext = getServletContext();

        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        File baseDirectory = applicationProfile.getBaseDirectory();
        
        String filesystemLog;
        
        FilesystemValidationService validationService = applicationProfile.getFilesystemValidationService();

        boolean notValid = !validationService.validatePath(baseDirectory, path);

        if(notValid)
        {
            filesystemLog = "An invalid path was given: " + path;
        }
        else
        {
            File directoryToCreate = new File(baseDirectory, path);

            if( directoryToCreate.exists() )
            {
                filesystemLog = "The file alredy exists: " + directoryToCreate.getAbsolutePath();
            }
            else
            {
                boolean wasCreated = directoryToCreate.mkdirs();

                filesystemLog = "The directory (" 
                                + directoryToCreate.getAbsolutePath()
                                + ") creation status: "
                                + wasCreated;
            }   
        }            

        return filesystemLog;
    }
}
