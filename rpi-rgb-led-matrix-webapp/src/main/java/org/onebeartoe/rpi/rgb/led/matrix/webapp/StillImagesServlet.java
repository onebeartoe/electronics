
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import static org.onebeartoe.rpi.rgb.led.matrix.webapp.AnimationsServlet.animationsPath;
import org.onebeartoe.system.OperatingSystem;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 * 
 */
@WebServlet(name = "StillImagesServet", urlPatterns = {"/still-images/*"})
public class StillImagesServlet extends HttpServlet 
{
    //TODO: Make this a member of the RaspberryPiRgbedMatrix class!
    public static String stillImagesPath = "/home/pi/rpi-rgb-led-matrix-images/stills/";
    
    private File stillImagesDirectory;
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
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
        rd.forward(request, response);
    }
    
    @Override
    public void init() throws ServletException
    {
        OperatingSystem os = new OperatingSystem();
        if( os.seemsLikeMsWindows() )
        {
            // adjust the target host from explicit paths on Raspberry Pi to 
            // development development location (user home).
            String userhome = System.getProperty("user.home") + "/";
            
            stillImagesPath = stillImagesPath.replace("/home/pi/", userhome);
        }
        
        stillImagesDirectory = new File(stillImagesPath);
        stillImagesDirectory.mkdirs();
    }    
}
