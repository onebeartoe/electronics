
package org.onebeartoe.rpi.rgb.led.matrix.webapp;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import org.onebeartoe.io.ObjectRetriever;
import org.onebeartoe.rpi.rgb.led.matrix.RaspberryPiRgbLedMatrix;
import org.onebeartoe.system.OperatingSystem;

/**
 *
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
public abstract class RaspberryPiRgbLedMatrixServlet extends HttpServlet
{
    protected final OperatingSystem os;
    
    protected final Logger logger;
    
    public static final String LED_MATRIX_HAT_CONTEXT_KEY = "LED_MATRIX_HAT_CONTEXT_KEY";
    
//    protected static RaspberryPiRgbLedMatrix ledMatrix;

    protected static File configFile;

    public RaspberryPiRgbLedMatrixServlet()
    {
        logger = Logger.getLogger(getClass().getName());
        
        os = new OperatingSystem();
    }
    
    private void adjustIfOnWindows(RaspberryPiRgbLedMatrix ledMatrix)
    {
        if( os.seemsLikeMsWindows() )
        {
            // adjust the target host from explicit paths on Raspberry Pi to 
            // development development location (user home).
            String userhome = os.currentUserHome() + "/";
            String badUserhome = "/home/pi/";
            
            String animationsPath = ledMatrix.getAnimationsPath().replace(badUserhome, userhome);
            String stillImagesPath = ledMatrix.getStillImagesPath().replace(badUserhome, userhome);
            
            ledMatrix.setAnimationsPath(animationsPath);
            ledMatrix.setStillImagesPath(stillImagesPath);
        }
    }
    
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
    
    /**
     * This initializes the RaspberryPiRgbLedMatrix object referenced throughout
     * the application.
     * 
     * If the RaspberryPiRgbLedMatrix object retrieved from persistence has a null
     * value for either the animations or still images directory, the defaults values 
     * are used and directories for the default values are created.
     * 
     * @throws ServletException 
     */
    @Override
    public void init() throws ServletException
    {
        super.init();

        initializeLedMatix();
    }
    
    private void initializeLedMatix()
    {
        ServletContext servletContext = getServletContext();
        
        RaspberryPiRgbLedMatrix ledMatrix;
        
        ledMatrix = (RaspberryPiRgbLedMatrix) servletContext.getAttribute(LED_MATRIX_HAT_CONTEXT_KEY);
        if(ledMatrix == null)
        {
            // this is the first time the application loads this servlet
            try
            {
                ledMatrix = restoreFromPersistence();
            }
            catch(Exception e)
            {
                String message = "The ledMatix configuration was not retieved from storage.";
                logger.log(Level.SEVERE, message, e);
            }
            
            if(ledMatrix == null)
            {
                ledMatrix = loadDefaults();
            }
            
            adjustIfOnWindows(ledMatrix);
        }        
        
        // make the RaspberryPiRgbLedMatrix object available to the servlet context
        servletContext.setAttribute(LED_MATRIX_HAT_CONTEXT_KEY, ledMatrix);
    }

    private RaspberryPiRgbLedMatrix loadDefaults()
    {
        // retore didn't work
        RaspberryPiRgbLedMatrix ledMatrix = new RaspberryPiRgbLedMatrix();

        String rpiLgbLedMatrixHome = "/home/pi/rpi-rgb-led-matrix";
        ledMatrix.setRpiLgbLedMatrixHome(rpiLgbLedMatrixHome);
                
        // set up the default image/animation paths
        String animationsPath = "/home/pi/rpi-rgb-led-matrix-images/animations/";        
        ledMatrix.setAnimationsPath(animationsPath);
        File animationsDir = new File(animationsPath);
        animationsDir.mkdirs();
        
        String stillImagesPath = "/home/pi/rpi-rgb-led-matrix-images/stills/";        
        ledMatrix.setStillImagesPath(stillImagesPath);
        File stillImagesDirectory = new File(stillImagesPath);
        stillImagesDirectory.mkdirs();
        
        // default to what worked with this panel and hat
        //      https://www.adafruit.com/products/1484
        //      https://www.adafruit.com/products/2345
        //
        String [] commandLineFlags = {"--led-no-hardware-pulse", 
                                      "--led-gpio-mapping=adafruit-hat"};
        
        ledMatrix.setCommandLineFlags(commandLineFlags);
        
        return ledMatrix;
    }
    
    private RaspberryPiRgbLedMatrix restoreFromPersistence() throws FileNotFoundException
    {
        String configDirPath = os.currentUserHome() + "/.onebeartoe/rpi-rgb-led-matrix-webapp/";
        File configDir = new File(configDirPath);
        configDir.mkdirs();
        
        configFile = new File(configDir, "led-matrix-webapp.xml");
        
        Object object = ObjectRetriever.decodeObject(configFile);
        
        RaspberryPiRgbLedMatrix ledMatrix = (RaspberryPiRgbLedMatrix) object;
        
        return ledMatrix;
    }
}
