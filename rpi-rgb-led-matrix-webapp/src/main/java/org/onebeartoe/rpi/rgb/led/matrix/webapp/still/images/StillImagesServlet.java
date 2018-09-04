
package org.onebeartoe.rpi.rgb.led.matrix.webapp.still.images;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.rpi.rgb.led.matrix.webapp.RaspberryPiRgbLedMatrixServlet;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 * 
 */
@WebServlet(name = "StillImagesServet", urlPatterns = {"/still-images/*"})
public class StillImagesServlet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    {
        doResponse(request, response);
    }
    
    protected void doResponse(HttpServletRequest request, HttpServletResponse response)
    {
        File stillImagesDirectory = new File( ledMatrix.getStillImagesPath() );
        String[] fileNames = stillImagesDirectory.list(new FilenameFilter() 
        {
            @Override
            public boolean accept(File dir, String name) {
                return name.endsWith(".png");
            }
        });
        request.setAttribute("stillImageNames", fileNames);
        
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/WEB-INF/jsp/still-images/index.jsp");
        try        
        {
            rd.forward(request, response);
        } 
        catch (IOException | ServletException ex)
        {
            Logger.getLogger(StillImagesServlet.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
