
package org.onebeartoe.weather.station.relay;

import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.TooManyListenersException;
import java.util.logging.Logger;
import org.onebeartoe.io.serial.SerialPorts;

import org.onebeartoe.web.adafruit.io.FeedData;

/**
 * This class manages a Serial connection and listens for Arduino messages.
 * 
 * @author Roberto Marquez
 */
public class WeatherStationSerialListener implements SerialPortEventListener
{    
    private BufferedReader input;

    private FeedData feedData;
    
    private SerialPort serialPort;
    
    private CliWeatherStationRelayRunProfile runProfile;
    
    private Logger logger;
    
    public WeatherStationSerialListener(CliWeatherStationRelayRunProfile runProfile) throws PortInUseException, UnsupportedCommOperationException, 
                                                 IOException, TooManyListenersException, Exception
    {
        logger = Logger.getLogger( getClass().getName() );
        
        this.runProfile = runProfile;
        
        serialPort = SerialPorts.get( runProfile.getPortName() );
        
        // open the streams
        InputStream is = serialPort.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        input = new BufferedReader(isr);

        // add event listeners
        serialPort.addEventListener(this);
    }
            
    public void closeSerialPort()
    {
        
        if(serialPort != null)
        {
            serialPort.removeEventListener();
            
            serialPort.close();
        }
    }
    
    public FeedData getFeedData()
    {
        return feedData;
    }

    private boolean isValid(FeedData feedData)
    {
        FeedData target = lookup(feedData);
        
        return target != null;
    }
    
    private FeedData lookup(FeedData feedData)
    {
        FeedData target = runProfile.getFeedDataList()
                                    .stream()
                                    .filter( fd -> feedData.getTopic().equals( fd.getTopic() ))
                                    .findAny()
                                    .orElse(null);

        return target;
    }
    
    /**
     * Handle an event on the serial port. Read the data and print it.
     */
    @Override
    public synchronized void serialEvent(SerialPortEvent event) 
    {
        if(event.getEventType() == SerialPortEvent.DATA_AVAILABLE) 
        {
            try 
            {
                String inputLine = input.readLine();

                feedData = FeedData.valueOf(inputLine);
              
                System.out.println(inputLine);
                System.out.println();
                
                boolean valid = isValid(feedData);
                
                if(valid)
                {
                    updateFeedDataList(feedData);
                }
                else
                {
                    String message = "unknown topic was dropped >" + inputLine + "<" + "\n";
                    
                    logger.warning(message);
                }
            } 
            catch (Exception e) 
            {
                System.err.println(e.toString());
            }
        }
    }

    private void updateFeedDataList(FeedData feedData)
    {
        FeedData target = lookup(feedData);
        
        String newValue = feedData.getValue();
        
        target.setValue(newValue);
    }
}
