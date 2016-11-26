
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.util.logging.Logger;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import org.onebeartoe.rpi.rgb.led.matrix.RaspberryPiRgbLedMatrixHat;
import static org.onebeartoe.rpi.rgb.led.matrix.webapp.AnimationServet.LED_MATRIX_HAT_CONTEXT_KEY;
import org.onebeartoe.web.PlainTextResponseServlet;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
public abstract class RaspberryPiRgbLedMatrixHatServlet extends PlainTextResponseServlet
{
    protected Logger logger;
    
    public static final String LED_MATRIX_HAT_CONTEXT_KEY = "LED_MATRIX_HAT_CONTEXT_KEY";
    
    protected RaspberryPiRgbLedMatrixHat ledMatrixHat;

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() 
    {
        return "Short description for " + getClass().getName();
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
