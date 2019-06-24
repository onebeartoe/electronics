/*
 */
package org.onebeartoe.wav.to.dot.h;

import java.io.IOException;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.CommandLineInterfaceApplet;
import org.onebeartoe.application.RunProfile;

/**
 *
 * @author Roberto Marquez
 */
public class WavToDotH extends CommandLineInterfaceApplet
{
    @Override
    public Options buildOptions()
    {
        
        Options options = new Options();
      
        options.addOption(subject);
        
        return options;        
        
    }    
    
    protected AppletService getService() 
    {
        return new WavToDotHService();
    }    
    
    public static void main(String [] args) throws IOException, Exception
    {
        CommandLineInterfaceApplet app = new WavToDotH();
        app.execute(args);
    }

    @Override
    protected RunProfile parseRunProfile(final String[] args, Options options) throws ParseException
    {
        WavToDotHRunProfile profile = new WavToDotHRunProfile();
        
        
        
        return profile;
    }    
}




