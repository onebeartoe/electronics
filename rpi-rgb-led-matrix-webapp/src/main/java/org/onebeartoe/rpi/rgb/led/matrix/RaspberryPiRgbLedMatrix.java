
package org.onebeartoe.rpi.rgb.led.matrix;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
public class RaspberryPiRgbLedMatrix implements Serializable
{
    private transient Logger logger;
    
    private transient Process commandProcess;
    
    private String animationsPath;
    
    private String stillImagesPath;
    
    private String [] commandLineFlags;
    
    private String scrollingText;
    
    /**
     * This is the directory where the rpi-rgb-led-matrix project was cloned to 
     * on the filesystem.
     */
    private String rpiRgbLedMatrixHome =  "/home/pi/rpi-rgb-led-matrix";
    
    // loop forever!
    private static final String LOOP_FOREVER_PARAMETER = "-f";
    
    public RaspberryPiRgbLedMatrix()
    {
        logger = Logger.getLogger(getClass().getName());
        
        commandLineFlags = new String[0];
    }

    public String getAnimationsPath()
    {
        return animationsPath;
    }
    
    public String [] getCommandLineFlags()
    {
        return commandLineFlags;
    }
    
    public String getRpiRgbLedMatrixHome()
    {
        return rpiRgbLedMatrixHome;
    }
    
    public String getScrollingText()
    {
        return scrollingText;
    }
    
    public String getStillImagesPath()
    {
        return stillImagesPath;
    }
    
    public void setAnimationsPath(String animationsPath)
    {
        this.animationsPath = animationsPath;
    }
    
    public void setCommandLineFlags(String [] flags)
    {
        this.commandLineFlags = flags;
    }
    
    public void setRpiLgbLedMatrixHome(String rpiLgbLedMatrixHome)
    {
        this.rpiRgbLedMatrixHome = rpiLgbLedMatrixHome;
    }
    
    public void setScrollingText(String text)
    {
        scrollingText = text;
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
        String gifPath = animationsPath + gifName;
                
        startLedImageViewerCommand(gifPath);

        logger.log(Level.INFO, "animation process wait over");
    }
    
    /**
     * The image would only stay on for 1.5 seconds without the -f flag.
     * @param gifPath
     * @throws IOException 
     */
    private void startLedImageViewerCommand(String gifPath) throws IOException
    {
        String executable = rpiRgbLedMatrixHome + "/utils/led-image-viewer";
        
        List<String> command = new ArrayList();
        command.add(executable);
        command.addAll( Arrays.asList(commandLineFlags) );
        command.add(LOOP_FOREVER_PARAMETER);
        command.add(gifPath);
        
        String debugList = "";
        for(String s : command)
        {
            debugList += s + " ";
        }
        
        String debugInfo = "command list: >" + debugList + "<";
        logger.log(Level.INFO, debugInfo);
        
        
        logger.log(Level.INFO, "staring still image process");
        ProcessBuilder builder = new ProcessBuilder(command);

        commandProcess = builder.start();

        // do not waitFor() the process to finish, so as to keep the Web UI responsive
    }

    public void startScrollingTextCommand(String text) throws IOException
    {
        try 
        {
            stopCommand();
        } 
        catch (InterruptedException ex) 
        {
            String message = "The comamnd could not be stopped: " + ex.getMessage();
            logger.log(Level.SEVERE, message, ex);
            
            Thread.currentThread().interrupt();
        }
        
        String execuableParent = rpiRgbLedMatrixHome + "/python/samples/";
        File workingDir = new File(execuableParent);
        String executable = execuableParent + "runtext.py";
        
        List<String> command = new ArrayList();
        command.add(executable);
        logger.log(Level.INFO, "commandLineFlags.length: " + commandLineFlags.length);
        if(commandLineFlags.length > 0)
        {
            if(commandLineFlags.length == 1 && commandLineFlags[0].trim().equals("") )
            {
                logger.log(Level.INFO, "a single blank command line flag exists but will not be used");            
            }
            else
            {
                command.addAll( Arrays.asList(commandLineFlags) );
                
                StringBuilder cliFlags = new StringBuilder();
                Arrays.stream(commandLineFlags)
                                    .forEach(s -> cliFlags.append(s + "< >") );
                
                logger.log(Level.INFO, "command line flags: " + cliFlags);            
            }
        }
        else
        {
            logger.log(Level.INFO, "no commandline flags are present");
        }

        command.add("--text");
        command.add(text);
        
        StringBuilder debugList = new StringBuilder();
        for(String s : command)
        {
            debugList.append(s + " ");
        }
        logger.log(Level.INFO, "command list: >" + debugList.toString() + "<");
        
        logger.log(Level.INFO, "starting scrolling text process...");
        ProcessBuilder builder = new ProcessBuilder(command);
        
        // use the directory() method to cd to the runtext.py location; needed becuase the 
        // that code currently uses a relative path the font file.
        builder.directory(workingDir);
        
        commandProcess = builder.start();
        
        logger.log(Level.INFO, "after process start, builder directory is: " + builder.directory() );
    }
    
    public void startShowStillImageCommand(String stillImageName) throws IOException
    {        
        String imagePath = stillImagesPath + stillImageName;
                
        startLedImageViewerCommand(imagePath);
        
        String infoMessage = "still image process wait over for: " + imagePath;
        logger.log(Level.INFO, infoMessage);        
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
}
