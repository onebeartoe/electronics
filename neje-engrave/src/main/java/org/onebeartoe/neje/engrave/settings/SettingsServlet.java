
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
    
    private static ApplicationProfile applicationProfile;
    
    private static NejeEngraver engraver;
    
    public SettingsServlet()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    {      
        doResponse(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    {

        String stillsDirtory = request.getParameter("EzGraverCli");
        engraver.setCliExecutable(stillsDirtory);

        
        File outfile = new File(applicationProfile.getBaseDirectory(), ApplicationProfile.CONFIGURATION_FILENAME);
        ObjectSaver.encodeObject(engraver, outfile);
        
        String saveMessages = "Settings changes were saved.";        
        request.setAttribute("saveMessages", saveMessages);
        
        doResponse(request, response);
    }

    private void doResponse(HttpServletRequest request, HttpServletResponse response)
    {
        File bd = applicationProfile.getBaseDirectory();
        String imageDirectory = bd.getAbsolutePath();
        request.setAttribute("baseDir", imageDirectory);
        
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

    @Override
    public void init() throws ServletException
    {
        super.init();
        
        ServletContext servletContext = getServletContext();

        applicationProfile = (ApplicationProfile) servletContext.getAttribute(APPLICTION_PROFILE_CONTEXT_KEY);
        
        engraver = applicationProfile.getEngraver();
    }
}