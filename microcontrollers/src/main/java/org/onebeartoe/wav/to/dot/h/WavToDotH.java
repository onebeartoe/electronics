/*
 */
package org.onebeartoe.wav.to.dot.h;

import java.io.File;
import java.io.IOException;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.Option;
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
    final private String WAV_FILE = "wavFile";
    
    @Override
    public Options buildOptions()
    {
         Option wavFile = Option.builder()
                        .required()
                        .hasArg()
                        .longOpt(WAV_FILE)
                        .desc("This is the email address of the recipient.")
                        .build();
        
        
        Options options = new Options();
        
        
      
        options.addOption(wavFile);
        
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
        CommandLineParser parser = new DefaultParser();

        CommandLine cl = parser.parse(options, args);
        
        WavToDotHRunProfile profile = new WavToDotHRunProfile();
        
        String wavFilePath = cl.getOptionValue(WAV_FILE);
        
        File wavFile = new File(wavFilePath);

        profile.setWavFile(wavFile);
        
        return profile;
    }    
}
