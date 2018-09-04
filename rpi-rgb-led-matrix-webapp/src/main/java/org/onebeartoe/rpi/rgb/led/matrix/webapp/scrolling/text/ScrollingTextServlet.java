
package org.onebeartoe.rpi.rgb.led.matrix.webapp.scrolling.text;

import java.io.File;
import java.io.IOException;
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
 * Here is a sample command with the --text (-t) option to specify the text to 
 * scroll on the RGB LED matrix:
 * 
 *      sudo ./runtext.py -t "I love-you! <3"
 * 
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
@WebServlet(name = "ScrollingTextServet", urlPatterns = {"/scrolling-text/*"})
public class ScrollingTextServlet extends RaspberryPiRgbLedMatrixServlet
{
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    {      
        doResponse(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    {
        String text = request.getParameter("text");
        String saveMessages;
        
        ServletContext servletContext = getServletContext();
        RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);        
        
        try
        {
            ledMatrix.setScrollingText(text);        
            ledMatrix.startScrollingTextCommand(text);
            saveMessages = "The scrolling text was updated.";
        }
        catch(Exception e)
        {
            saveMessages = "An error occured while updating the scrolling text: "
                            + e.getMessage();
            
            logger.log(Level.SEVERE, saveMessages, e);
        }

        // save the updated scrolling text configuration
        File outfile = configFile;
        ObjectSaver.encodeObject(ledMatrix, outfile);
        
        request.setAttribute("responseMessages", saveMessages);
        doResponse(request, response);
    }
    
    private void doResponse(HttpServletRequest request, HttpServletResponse response)
    {
        ServletContext servletContext = getServletContext();
        RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);                
        
        request.setAttribute("ledMatrix", ledMatrix);
                
        ServletContext c = getServletContext();
        RequestDispatcher rd = c.getRequestDispatcher("/WEB-INF/jsp/scrolling-text/index.jsp");
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
