
package org.onebeartoe.rpi.rgb.led.matrix.webapp.settings;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.io.ObjectSaver;
import org.onebeartoe.rpi.rgb.led.matrix.RaspberryPiRgbLedMatrix;
import org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet;
import static org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet.LED_MATRIX_HAT_CONTEXT_KEY;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(name = "SettingsServet", urlPatterns = {"/settings/*"})
public class SettingsServlet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    {      
        doResponse(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        ServletContext servletContext = getServletContext();
        RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);        
        
        String stillsDirtory = request.getParameter("stillImagesDirectory");
        ledMatrix.setStillImagesPath(stillsDirtory);
        
        String animationsDirectory = request.getParameter("animationsDirectory");
        ledMatrix.setAnimationsPath(animationsDirectory);
        
        String rpiRgbLedMatrixHome = request.getParameter("rpiRgbLedMatrixHome");
        ledMatrix.setRpiLgbLedMatrixHome(rpiRgbLedMatrixHome);
        
        String s = request.getParameter("commandLineFlags");
        if(s == null)
        {
            s = "";
        }
        String[] flags = s.split("\\s+");
        ledMatrix.setCommandLineFlags(flags);

        File outfile = configFile;
        ObjectSaver.encodeObject(ledMatrix, outfile);
        
        String saveMessages = "Settings changes were saved.";        
        request.setAttribute("saveMessages", saveMessages);
        doResponse(request, response);
    }

    private void doResponse(HttpServletRequest request, HttpServletResponse response)
    {
        ServletContext servletContext = getServletContext();
        RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);        
        
        request.setAttribute("ledMatrix", ledMatrix);
        
        List list = Arrays.asList( ledMatrix.getCommandLineFlags() );
        String rpiRgbLedMatrixHome = String.join(" ", list);                
        request.setAttribute("commandLineFlags", rpiRgbLedMatrixHome);
                
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/WEB-INF/jsp/settings/index.jsp");
        try        
        {
            rd.forward(request, response);
        } 
        catch (IOException | ServletException ex)
        {
            logger.log(Level.SEVERE, null, ex);
        }
    }
}
