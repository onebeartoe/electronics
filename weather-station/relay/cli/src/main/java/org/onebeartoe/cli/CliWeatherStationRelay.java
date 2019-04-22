
package org.onebeartoe.cli;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;
import java.util.Properties;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.commons.lang3.StringUtils;
import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.CommandLineInterfaceApplet;
import org.onebeartoe.application.RunProfile;
import org.onebeartoe.io.serial.SerialPorts;
import org.onebeartoe.weather.station.relay.CliWeatherStationRelayRunProfile;
import org.onebeartoe.weather.station.relay.WeatherStationRelayService;

/**
 * This application starts a deamon thread to periodically send data to an Internet
 * of things platform, AdafruitIO.
 * 
 * To end the program send the 'q' character to the standard input stream of the application.
 * 
 * On Linux this command works with the RXTX provided by apt-get:
 *
 *      sudo apt-get install librxtx-java
 * 
 *      cd /usr/lib/jni/
 * 
 *      sudo ln -s librxtxSerial-2.2pre1.so rxtxSerial.so
 * 
 *      java -Djava.library.path=/usr/lib/jni/ -jar extreme-notifications-1.0-SNAPSHOT-jar-with-dependencies.jar /dev/ttyACM0 strip-job.mapping
 * 
 * @author Roberto Marquez
 */
public class CliWeatherStationRelay extends CommandLineInterfaceApplet
{
    private final String LIBRARY_PATH = "libraryPath";
    
    private final String PROPERTIES_PATH = "propertiesPath";
    
    @Override
    public Options buildOptions()
    {
        Option libraryPath = Option.builder()
                                .hasArg()
                                .longOpt(LIBRARY_PATH)
                                .build();
        
        Option propertiesPath = Option.builder()
                                .hasArg()
                                .longOpt(PROPERTIES_PATH)
                                .required()
                                .build();
        
        Options options = new Options();
        options.addOption(libraryPath);
        options.addOption(propertiesPath);
        
        return options;        
    }
    
    @Override
    protected AppletService getService() 
    {
        return new WeatherStationRelayService();
    }
    
    public static void main(String [] args) throws Exception
    {
        
        
        Thread relayThread = new Thread(() ->
        {
            System.out.println("running dameon code");
        });
        
        relayThread.setDaemon(true);
        
//        relayThread.
        
        CommandLineInterfaceApplet app = new CliWeatherStationRelay();        
        app.execute(args);
       
        int c = System.in.read();
        
        while( c != (char)'q')
        {
            c = System.in.read();
        }
    }
    
    @Override
    protected RunProfile parseRunProfile(final String[] args, Options options) throws ParseException
    {
        String key = "java.library.path";
        String libPath = System.getProperty(key);
        
        logger.info(key + ": " + libPath + "\n");
        
        if(StringUtils.isBlank(libPath))
        {

            List<String> ports = SerialPorts.list();

            final StringBuffer message = new StringBuffer("The '" + key + "' system property is not set."
                                + "Available serial ports:");
            
            ports.forEach( p -> message.append(p) );

            throw new ParseException(message.toString() );
        }
        
        CommandLineParser parser = new DefaultParser();
        CommandLine cl = parser.parse(options, args);

        CliWeatherStationRelayRunProfile runProfile = new CliWeatherStationRelayRunProfile();

        if( cl.hasOption(LIBRARY_PATH) )
        {
            String path = cl.getOptionValue(LIBRARY_PATH);

            runProfile.setLibraryPath(path);
        }

        runProfile.setPropertiesPath( cl.getOptionValue(PROPERTIES_PATH) );
        Properties props = new Properties();
        InputStream inStream;
        
        try
        {
            inStream = new FileInputStream(runProfile.getPropertiesPath() );
            props.load(inStream);
        }
        catch (IOException ex)
        {
            String message = "An error occurred while reading the properties file: " + ex.getMessage() ;
            
            logger.severe(message);
            
            throw new ParseException(message.toString() );
        }
        
        List<String> remainingArgs = cl.getArgList();

        if(remainingArgs.size() > 0)
        {
            remainingArgs.forEach(System.out::println);
        }        
        
        return runProfile;
    }    
}
