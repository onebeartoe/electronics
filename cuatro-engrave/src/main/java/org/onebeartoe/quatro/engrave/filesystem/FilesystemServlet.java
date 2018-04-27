
package org.onebeartoe.quatro.engrave.filesystem;

import java.io.File;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.logging.Logger;
import java.util.stream.Collectors;
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
        
        request.setAttribute("subpath", subpath);
        
        String currentDirectory = subpath;
        
        StringBuilder responseText = new StringBuilder();
        
        responseText.append(currentDirectory);
        responseText.append("<br>\n<br>");
        
        File [] files = null;
        
        File baseDir = applicationProfile.getBaseDirectory();

        File directory = new File(baseDir, subpath);
        
        try
        {
            filesystemValidationService.validatePath(baseDir, subpath);        

            logger.info("directory: " + directory.getAbsolutePath() );

            files = directory.listFiles();
            
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
            List<File> sortedFiles = Arrays.stream(files)
                                           .sorted( Comparator.comparing( File::isDirectory ) 
//                                                    .thenComparing(File::getName)
                                            .reversed() 
                                                            )
//                                           .collect( Collectors.groupingBy( f -> f.getName() ) ) ;
                                           .collect( Collectors.toList() );
            
            for(File f : sortedFiles)
            {
                responseText.append("<br/>");
                
                String markup = markup(f);
                responseText.append(markup);
                
                responseText.append("<br/>");
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
    
    private String markup(File file)
    {
        StringBuilder markup = new StringBuilder();
        
        String name = file.getName();

        if( file.isDirectory() )
        {
// TODO: start using an object to toString() the HTML elemnts: org.onebeartoe.HtmlTag
            
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
                          + " "
                          + "<button onclick=\"uploadImageToEngraver('" + path + "')\" >" 
                          + "Upload to Engraver" 
                          + "</button>");
        }
        
        return markup.toString();
    }
}
