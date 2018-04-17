
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
    public void startEngraving() throws IOException
    {        
        String executable = "/home/roberto/Versioning/group/github/camrein/EzGraver-unix_cli_fixes/EzGraverCli/EzGraverCli";
        
        List<String> command = new ArrayList();
        command.add(executable);
        command.add("s");
        command.add("/dev/ttyUSB0");
        
        String debugList = "";
        for(String s : command)
        {
            debugList += s + " ";
        }
        Logger logger = Logger.getAnonymousLogger();        
        logger.log(Level.INFO, "command list: >" + debugList + "<");        
        
        logger.log(Level.INFO, "staring engraving process");
        ProcessBuilder builder = new ProcessBuilder(command);

        Process commandProcess = builder.start();
    }    
}
