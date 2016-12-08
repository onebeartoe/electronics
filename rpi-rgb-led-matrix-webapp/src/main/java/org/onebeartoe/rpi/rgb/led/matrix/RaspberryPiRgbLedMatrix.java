
package org.onebeartoe.rpi.rgb.led.matrix;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Serializable;
import static java.nio.file.Files.list;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Collectors;

/**
 * @author Roberto Marquez <https://www.youtube.com/user/onebeartoe>
 */
public class RaspberryPiRgbLedMatrix implements Serializable
{
    private Logger logger;
    
    private Process commandProcess;
    
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
    private static final String loopForeverParameter = "-f";
    
    public RaspberryPiRgbLedMatrix()
    {
        logger = Logger.getLogger(getClass().getName());
        
        commandLineFlags = new String[0];
    }
    
    /**
     * Only call this during debugging.
     * Remove after debugging, because it was causing the processes to hang while 
     * blocking for stdin and stderr input.
     */
    private void dumpProcessOutput()
    {
        String stdout;
        try
        {
            InputStream stdin = commandProcess.getInputStream();
            InputStreamReader isr = new InputStreamReader(stdin);
            BufferedReader buffer = new BufferedReader(isr);
            stdout = buffer.lines().collect(Collectors.joining("\n"));
        }
        catch(Exception e)
        {
            stdout = e.getMessage();
        }
        
        StringBuilder sb = new StringBuilder("Standard out:\n");
        sb.append(stdout);
     
        String stderr;
        try
        {
            InputStream errorStream = commandProcess.getErrorStream();
            InputStreamReader errorIsr = new InputStreamReader(errorStream);
            BufferedReader errorBuffer = new BufferedReader(errorIsr);
            stderr = errorBuffer.lines().collect(Collectors.joining("\n"));
            sb.append("\nStandard Error:\n");
        }
        catch(Exception e)
        {
            stderr = e.getMessage();
        }
        sb.append(stderr);
        
        logger.log(Level.INFO, sb.toString());
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
//        int loopCount = 20;
//        String loopParameter = "-l" + loopCount;
        
//        UserOptions options = new UserOptions();
//        options.loopParameter = loopForeverParameter;
        
        String gifPath = animationsPath + gifName;
                
        startLedImageViewerCommand(gifPath);
//        startLedImageViewerCommand(options, gifPath);
        
        logger.log(Level.INFO, "animation process wait over");
    }
    
    private void startLedImageViewerCommand(String gifPath) throws IOException
//    private void startLedImageViewerCommand(UserOptions userOptions, String gifPath) throws IOException
    {
        String executable = rpiRgbLedMatrixHome + "/utils/led-image-viewer";
        
        List<String> command = new ArrayList();
        command.add(executable);
        command.addAll( Arrays.asList(commandLineFlags) );
        command.add(loopForeverParameter);
        command.add(gifPath);
        
        String debugList = "";
        for(String s : command)
        {
            debugList += s + " ";
        }
        logger.log(Level.INFO, "command list: >" + debugList + "<");
        
        
        logger.log(Level.INFO, "staring still image process");
        ProcessBuilder builder = new ProcessBuilder(command);

        commandProcess = builder.start();

        // do not wait for the process to finish, so as to keep the Web UI responsive        
//        logger.log(Level.INFO, "waiting for animation process");
//        int waitValue = commandProcess.waitFor();
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
        }
        
        String execuableParent = rpiRgbLedMatrixHome + "/python/samples/";
        File workingDir = new File(execuableParent);
        String executable = execuableParent + "runtext.py";
        
        List<String> command = new ArrayList();
        command.add(executable);
        command.addAll( Arrays.asList(commandLineFlags) );
        command.add("--text");
        command.add(text);
        
        String debugList = "";
        for(String s : command)
        {
            debugList += s + " ";
        }
        logger.log(Level.INFO, "command list: >" + debugList + "<");
        
        logger.log(Level.INFO, "starting scrolling text process...");
        ProcessBuilder builder = new ProcessBuilder(command);
        
        // use the directory() method to cd to the runtext.py location; needed becuase the 
        // that code currently uses a relative path the font file.
        builder.directory(workingDir);
        
        commandProcess = builder.start();
    }
    
    public void startShowStillImageCommand(String stillImageName) throws IOException
    {        
//        UserOptions options = new UserOptions();        
        
        // The image would only stay on for 1.5 seconds without the  -f flag.
//        options.loopParameter = loopForeverParameter;
        
        String imagePath = stillImagesPath + stillImageName;
                
        startLedImageViewerCommand(imagePath);
//        startLedImageViewerCommand(options, imagePath);
        
        logger.log(Level.INFO, "still image process wait over for: " + imagePath);        
    }
    
    /**
     * This sends a destroy message to the process, stopping execution.
     */
    public void stopCommand() throws InterruptedException
    {
        if(commandProcess != null)
        {
// removed this because it was causing the processes to hang            
//            dumpProcessOutput();
            
            commandProcess.destroy();
            commandProcess.waitFor();
        }
    }
    
    /**
     * This class represents the command line options that the led-image-viewer 
     * program supports.
     */
//    private class UserOptions
//    {
//        String loopParameter = "";
//    }
}
