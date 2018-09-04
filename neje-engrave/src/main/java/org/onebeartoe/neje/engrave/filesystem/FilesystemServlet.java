
package org.onebeartoe.neje.engrave.filesystem;

import java.io.File;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.logging.Logger;
import java.util.stream.Collectors;
import javax.servlet.ServletContext;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.html.BreakTag;
import org.onebeartoe.neje.engrave.ApplicationProfile;

import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 * This servlet handles requests for filesystem listings.
 */
@WebServlet(urlPatterns = {"/filesystem/*"})
public class FilesystemServlet extends PlainTextResponseServlet
{    
    private final Logger logger;

    private final BreakTag brTag = new BreakTag();
    
    private final String br = brTag.toHtml();
    
    public FilesystemServlet()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    @Override
    protected String buildText(HttpServletRequest request, HttpServletResponse response)
    {
        String subpath = request.getPathInfo();
        
        request.setAttribute("subpath", subpath);
        
        String currentDirectory = subpath;
        
        StringBuilder responseText = new StringBuilder();
        
        responseText.append(currentDirectory);
        responseText.append("<br>\n<br>");
        
        File [] files = null;
  
        ServletContext servletContext = getServletContext();
        
        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        File baseDir = applicationProfile.getBaseDirectory();

        File directory = new File(baseDir, subpath);
        
        try
        {
            FilesystemValidationService filesystemValidationService = applicationProfile.getFilesystemValidationService();
            filesystemValidationService.validatePath(baseDir, subpath);        

            logger.info("directory: " + directory.getAbsolutePath() );

            files = directory.listFiles();
            
        }
        catch(IllegalArgumentException ex)
        {
            String message = "An error occured while validating the path:" + ex.getMessage();
            
            logger.severe(message);
        }        
                        
        if(files == null)
        {
            responseText.append(br);
            responseText.append("no files are present: " + directory.getAbsolutePath() );
        }
        else
        {
            List<File> sortedFiles = Arrays.stream(files)
                                           .sorted( 
                                                Comparator.comparing( File::isDirectory ) 
                                                          .reversed() )
                                           .collect( Collectors.toList() );
            
            for(File f : sortedFiles)
            {
                responseText.append( br);
                
                String markup = markup(f, applicationProfile);
                responseText.append(markup);
                
                responseText.append( br);
                responseText.append( br);
            }
        }
        
        return responseText.toString();
    }
    
    private String markup(File file, ApplicationProfile applicationProfile)
    {
        StringBuilder markup = new StringBuilder();
        
        String name = file.getName();

        if( file.isDirectory() )
        {            
            String s = "<a onclick=\"updateFilesystem('/" + name + "');\"  href='#'>" + name + "/</a>";
            markup.append(s);
        }
        else if( file.isFile() )
        {
            String path = file.getAbsolutePath();
            
            File baseDir = applicationProfile.getBaseDirectory();
            
            String basePath = baseDir.getAbsolutePath() + "/";
            
            path = path.replace(basePath, "");
                    
            markup.append(name 
                          + "    "
                          + "<button onclick=\"uploadImageToEngraver('" + path + "')\" >" 
                          + "Upload to Engraver" 
                          + "</button>");
        }
        
        return markup.toString();
    }
}
