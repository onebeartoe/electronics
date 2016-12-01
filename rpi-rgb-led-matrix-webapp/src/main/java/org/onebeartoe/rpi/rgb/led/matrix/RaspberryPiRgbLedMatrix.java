
package org.onebeartoe.rpi.rgb.led.matrix;

import java.io.IOException;
import java.io.Serializable;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
public class RaspberryPiRgbLedMatrix implements Serializable
{
    private Logger logger;
    
    private Process commandProcess;
    
    private String animationsPath;
    
    private String stillImagesPath;
    
    // loop forever!
    private final String loopForeverParameter = "-f";
    
    public RaspberryPiRgbLedMatrix()
    {
        logger = Logger.getLogger(getClass().getName());
    }
    
    public String getAnimationsPath()
    {
        return animationsPath;
    }
    
    public void setAnimationsPath(String animationsPath)
    {
        this.animationsPath = animationsPath;
    }
    
    public String getStillImagesPath()
    {
        return stillImagesPath;
    }
    
    public void setStillImagesPath(String path)
    {
        stillImagesPath = path;
    }
    
    /**
     * Here is the original command to show an animation:
     * 
     *      ./led-image-viewer --led-no-hardware-pulse --led-gpio-mapping=adafruit-hat -l200 ../../bubbles.gif
     */
    public void startAnimationCommand(String gifName) throws IOException, InterruptedException
    {
        int loopCount = 20;
//        String loopParameter = "-l" + loopCount;
        
        UserOptions options = new UserOptions();
        options.loopParameter = loopForeverParameter;
        
        String gifPath = animationsPath + gifName;
                
        startLedImageViewerCommand(options, gifPath);
        
        logger.log(Level.INFO, "animation process wait over");
    }
    
    private void startLedImageViewerCommand(UserOptions userOptions, String gifPath) throws IOException
    {
        String executable = "/home/pi/rpi-rgb-led-matrix/utils/led-image-viewer";
        
        String [] list = {executable, "--led-no-hardware-pulse", "--led-gpio-mapping=adafruit-hat", userOptions.loopParameter, gifPath, "", ""};
        String debugList = "";
        for(String s : list)
        {
            debugList += s + ":";
        }
        logger.log(Level.INFO, "command list: " + debugList);
        List<String> command = Arrays.asList(list);
        
        logger.log(Level.INFO, "staring still image process");
        ProcessBuilder builder = new ProcessBuilder(command);

        commandProcess = builder.start();

        // do not wait for the process to finish, so as to keep the Web UI responsive        
//        logger.log(Level.INFO, "waiting for animation process");
//        int waitValue = commandProcess.waitFor();
    }

    public void startShowStillImageCommand(String stillImageName) throws IOException
    {        
        UserOptions options = new UserOptions();        
        
        // The image would only stay on for 1.5 seconds without the  -f flag.
        options.loopParameter = loopForeverParameter;
        
        String imagePath = stillImagesPath + stillImageName;
                
        startLedImageViewerCommand(options, imagePath);
        
        logger.log(Level.INFO, "still image process wait over for: " + imagePath);        
    }
    
    /**
     * This sends a destroy message to the process, stopping execution.
     */
    public void stopCommand() throws InterruptedException
    {
        if(commandProcess != null)
        {
            commandProcess.destroy();
            commandProcess.waitFor();
        }
    }
    
    /**
     * This class represents the command line options that the led-image-viewer 
     * program supports.
     */
    private class UserOptions
    {
        String loopParameter = "";
    }
}
