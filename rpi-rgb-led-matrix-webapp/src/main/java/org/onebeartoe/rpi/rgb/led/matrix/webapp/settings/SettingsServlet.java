
package org.onebeartoe.rpi.rgb.led.matrix.webapp.settings;

import java.io.File;
import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.io.ObjectSaver;
import org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(name = "SettingsServet", urlPatterns = {"/settings/*"})
public class SettingsServlet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {      
        doResponse(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        String stillsDirtory = request.getParameter("stillImagesDirectory");
        ledMatrix.setStillImagesPath(stillsDirtory);
        
        String animationsDirectory = request.getParameter("animationsDirectory");
        ledMatrix.setAnimationsPath(animationsDirectory);
        
        File outfile = RaspberryPiRgbLedMatrixServlet.configFile;
        ObjectSaver.encodeObject(ledMatrix, outfile);
        
        String saveMessages = "Settings changes were saved.";        
        request.setAttribute("saveMessages", saveMessages);
        doResponse(request, response);
    }
    
    private void doResponse(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        request.setAttribute("ledMatrix", ledMatrix);
                
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/WEB-INF/jsp/settings/index.jsp");
        rd.forward(request, response);        
    }
}
