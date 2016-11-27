
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
import org.onebeartoe.system.OperatingSystem;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 * 
 */
@WebServlet(name = "AnimationsServet", urlPatterns = {"/animations/*"})
public class AnimationsServlet extends HttpServlet
{
    public static String animationsPath = "/home/pi/rpi-rgb-led-matrix-images/animations/";
    
    private File animationsDir;

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        String[] fileNames = animationsDir.list(new FilenameFilter() {
            @Override
            public boolean accept(File dir, String name) {
                return name.endsWith(".gif");
            }
        });
        request.setAttribute("animationNames", fileNames);
        
        String entries = "lnmop";        
        request.setAttribute("cronTable", entries);
        
        
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/WEB-INF/jsp/animations/index.jsp");
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
            
            animationsPath = animationsPath.replace("/home/pi/", userhome);
        }
        
        animationsDir = new File(animationsPath);
        animationsDir.mkdirs();
    }
}
