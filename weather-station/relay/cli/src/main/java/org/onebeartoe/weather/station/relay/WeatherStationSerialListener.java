
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
    
    public WeatherStationSerialListener(CliWeatherStationRelayRunProfile runProfile) throws PortInUseException, UnsupportedCommOperationException, 
                                                 IOException, TooManyListenersException, Exception
    {
        serialPort = SerialPorts.get( runProfile.getPortName() );
        
        // open the streams
        InputStream is = serialPort.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        input = new BufferedReader(isr);

        // add event listeners
        serialPort.addEventListener(this);
    }
    
    public FeedData getFeedData()
    {
        return feedData;
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
            } 
            catch (Exception e) 
            {
                System.err.println(e.toString());
            }
        }
    }    

    public void closeSerialPort()
    {
        
        if(serialPort != null)
        {
            serialPort.removeEventListener();
            
            serialPort.close();
        }
    }
}
