
package org.onebeartoe.quatro.engrave;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Roberto Marquez
 */
public class NejeEngraver
{
    private final String executable = "/home/roberto/Versioning/group/github/camrein/EzGraver-unix_cli_fixes/EzGraverCli/EzGraverCli";

    private final String serialPort = "/dev/ttyUSB0";
    
    public void reset()
    {
        throw new UnsupportedOperationException();
    }
    
    private void sendEngraverCommand(char commandChar) throws IOException
    {

        List<String> command = new ArrayList();
        command.add(executable);
        command.add( String.valueOf(commandChar) );
        command.add(serialPort);
        
        String debugList = "";
        for(String s : command)
        {
            debugList += s + " ";
        }
        Logger logger = Logger.getAnonymousLogger();        
        logger.log(Level.INFO, "command list: >" + debugList + "<");        
        
        logger.log(Level.INFO, "staring engraving process");
        ProcessBuilder builder = new ProcessBuilder(command);

        builder.start();        
    }
    
    public void startEngraving() throws IOException
    {
        char command = 's';
        
        sendEngraverCommand(command);
    }    
}
