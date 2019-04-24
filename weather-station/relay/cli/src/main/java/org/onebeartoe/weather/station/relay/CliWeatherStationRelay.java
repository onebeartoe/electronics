
package org.onebeartoe.weather.station.relay;

import java.io.FileInputStream;
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
import org.onebeartoe.web.adafruit.io.FeedData;

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
    
    private final String PORT_NAME = "portName";
    
    private final String PROPERTIES_PATH = "propertiesPath";
    
    private CliWeatherStationRelayRunProfile runProfile;
    
    private CommandLine commandLine;
  
    private final String AIO_KEY = "AIO_KEY";
    
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

        Option portName = Option.builder()
                                .hasArg()
                                .longOpt(PORT_NAME)
                                .required()
                                .build();
                
        Options options = new Options();
        options.addOption(libraryPath);
        options.addOption(propertiesPath);
        options.addOption(portName);
        
        return options;        
    }
    
    @Override
    protected AppletService getService() 
    {
        return new WeatherStationRelayService();
    }
    
    @Override
    protected String getUsage()
    {
        StringBuffer usage = new StringBuffer();
        
        List<String> portList = SerialPorts.list();
        
        if(portList.size() > 0)
        {
            usage.append("\n");
            usage.append("the following serial communication ports were detected:");
            usage.append("\n");
            
            for(String port : portList)
            {
                usage.append("\t");
                usage.append(port);
            }
            usage.append("\n");
            usage.append("\n");
        }
        else
        {
            usage.append("no serial communication ports were detected");
        }
        
        return usage.toString();
    }
    
    public static void main(String [] args) throws Exception
    {
        CliWeatherStationRelay app = new CliWeatherStationRelay();        
        app.execute(args);
       
        System.out.println("\n" + "type 'q' to quit");
        System.out.println();
        
        int c = System.in.read();
        
        while( c != (char)'q')
        {
            c = System.in.read();            
        }
        
        app.terminateRelayThread();
    }
    
    @Override
    protected RunProfile parseRunProfile(final String[] args, Options options) throws ParseException
    {
        String key = "java.library.path";
        String libraryPath = System.getProperty(key);
        
        logger.info(key + ": " + libraryPath + "\n");
        
        if(StringUtils.isBlank(libraryPath))
        {
            List<String> ports = SerialPorts.list();

            final StringBuffer message = new StringBuffer("The '" + key + "' system property is not set."
                                + "Available serial ports:");
            
            ports.forEach( p -> message.append(p) );

            throw new ParseException(message.toString() );
        }
        
        CommandLineParser parser = new DefaultParser();
        commandLine = parser.parse(options, args);

        runProfile = new CliWeatherStationRelayRunProfile();
        
        if( commandLine.hasOption(LIBRARY_PATH) )
        {
            String path = commandLine.getOptionValue(LIBRARY_PATH);

            runProfile.setLibraryPath(path);
        }

        String portName = commandLine.getOptionValue(PORT_NAME);
        runProfile.setPortName(portName);                
        
        parseRunProfilePropertiesFile();
        
        List<String> remainingArgs = commandLine.getArgList();

        if(remainingArgs.size() > 0)
        {
            remainingArgs.forEach(System.out::println);
        }        
        
        this.runProfile = runProfile;
        
        return runProfile;
    }

    public void terminateRelayThread()
    {
        runProfile.setRelayStatus(RelayStatus.TERMINATED);
    }

    private void parseRunProfilePropertiesFile() throws ParseException
    {
        runProfile.setPropertiesPath(commandLine.getOptionValue(PROPERTIES_PATH) );
        
        Properties properties = new Properties();
            
        try
        {
            InputStream inStream = new FileInputStream(runProfile.getPropertiesPath() );
            properties.load(inStream);
            
            String s = properties.getProperty(AIO_KEY);
                        
            if( StringUtils.isBlank(s))
            {
                String message = "property '" + AIO_KEY + "' in file " + runProfile.getPropertiesPath() 
                                 + " cannot be blank";
                
                throw new ParseException(message);
            }
            else
            {
                String iotKey = s.trim();
                runProfile.setIotKey(iotKey);
            }
            
            parseRunProfilePropertiesFileTopics(properties);
        }
        catch (Exception ex)
        {
            String message = "An error occurred while reading the properties file: " + ex.getMessage() ;
            
            logger.severe(message);
            
            throw new ParseException(message.toString() );
        }
    }

    private void parseRunProfilePropertiesFileTopics(Properties properties) throws ParseException
    {
        String key = "topics";
        String s = properties.getProperty(key);
        
        if( StringUtils.isBlank(s) )
        {
            String message = "The properties file did not have an entry for '" + key + "'. "
                             + "Please add one and try again";
            
            logger.severe(message);
            
            throw new ParseException(message);
        }
        else
        {
            String[] split = s.split(",");
            
            for(String topic : split)
            {
                FeedData feedData = new FeedData();
                feedData.setTopic(topic);
                
                runProfile.getFeedDataList()
                          .add(feedData);
            }
        }
    }
}
