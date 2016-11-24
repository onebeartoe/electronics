
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.onebeartoe.rpi.rgb.led.matrix.RaspberryPiRgbLedMatrixHat;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 * 
 * An instance of this servlet is created on startup to ensure a Camera object 
 * is always an attribute in the ServletContext for the application.
 * 
 */
@WebServlet(name = "AnimationServet", urlPatterns = {"/animation/*"}, loadOnStartup = 1)
public class AnimationServet extends HttpServlet 
{
    private Logger logger;
    
    public static final String LED_MATRIX_HAT_CONTEXT_KEY = "LED_MATRIX_HAT_CONTEXT_KEY";
    
    private RaspberryPiRgbLedMatrixHat ledMatrixHat;
    
    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException 
    {
        
            String pi = request.getPathInfo();
            String operation = pi.substring(1); // remove the slash character
            
            ServletOutputStream outputStream = response.getOutputStream();
            
            PrintWriter pw = new PrintWriter(outputStream);
            logger.log(Level.INFO, "sending initial data to user..");
            pw.write("request recieved");
//TODO: Will the user see the message right above without the call to flush, without having to 
//      wait untal after startAnimationCommand()?
            pw.flush();

            try 
            {            
                ledMatrixHat.startAnimationCommand();
            } 
            catch (Exception ex) 
            {
                String message = "Error: " + ex.getMessage();
                pw.write("<br/><br/>" + message);
                logger.log(Level.SEVERE, message, ex);
            }
            
            String message = "request processed";
            logger.log(Level.INFO, message);
            
            String r = "<br/><br/>" + message;
            
            pw.write(r);        
            pw.flush();
            pw.close();
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() 
    {
        return "Short description";
    }
    
    @Override
    public void init() throws ServletException
    {
        super.init();
        
        logger = Logger.getLogger(getClass().getName());
        
        ServletContext servletContext = getServletContext();
        ledMatrixHat = (RaspberryPiRgbLedMatrixHat) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);
        if(ledMatrixHat == null)
        {
            ledMatrixHat = new RaspberryPiRgbLedMatrixHat();
            servletContext.setAttribute(LED_MATRIX_HAT_CONTEXT_KEY, ledMatrixHat);
        }        
    }
}
