
package org.onebeartoe.neje.engrave.settings;

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
import org.onebeartoe.io.ObjectSaver;
import org.onebeartoe.neje.engrave.ApplicationProfile;
import org.onebeartoe.neje.engrave.NejeEngraver;

import static org.onebeartoe.neje.engrave.StartEngraverServlet.APPLICTION_PROFILE_CONTEXT_KEY;

/**
 * This servlet handles requests to display and update the settings for the 
 * application.
 */
@WebServlet(urlPatterns = {"/settings/*"})
public class SettingsServlet extends HttpServlet
{
    private final Logger logger;
    
    public SettingsServlet()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    {
        ServletContext servletContext = getServletContext();

        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);        

        doResponse(request, response, applicationProfile);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        String ezgraverCommand = request.getParameter("EzGraverCli");

        ServletContext servletContext = getServletContext();

        ApplicationProfile applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);                

        NejeEngraver engraver = applicationProfile.getEngraver();

        engraver.setCliExecutable(ezgraverCommand);

        File outfile = new File(applicationProfile.getBaseDirectory(), ApplicationProfile.CONFIGURATION_FILENAME);
        ObjectSaver.encodeObject(engraver, outfile);
        
        String saveMessages = "Settings changes were saved.";        
        request.setAttribute("saveMessages", saveMessages);
        
        doResponse(request, response, applicationProfile);
    }

    private void doResponse(HttpServletRequest request, HttpServletResponse response, ApplicationProfile applicationProfile)
    {
        File bd = applicationProfile.getBaseDirectory();
        String imageDirectory = bd.getAbsolutePath();
        request.setAttribute("baseDir", imageDirectory);
        
        NejeEngraver engraver = applicationProfile.getEngraver();
        request.setAttribute("EzGraverCli", engraver.getCliExecutable());
                
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/WEB-INF/jsp/settings/index.jsp");
        
        try        
        {
            rd.forward(request, response);
        } 
        catch (IOException | ServletException ex)
        {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }
}