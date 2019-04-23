
package org.onebeartoe.weather.station.relay;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
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
    private SerialPort serialPort;
    
    private BufferedReader input;
    
    /**
     * Default bits per second for COM port.
     */
//    private final int DATA_RATE = 9600;
    /**
     * Milliseconds to block while waiting for port open
     */
//    private final int TIME_OUT = 2000;

    private List<FeedData> feedDataList;

    public WeatherStationSerialListener(CliWeatherStationRelayRunProfile runProfile) throws PortInUseException, UnsupportedCommOperationException, 
                                                 IOException, TooManyListenersException, Exception
    {
        SerialPort serialPort = SerialPorts.get( runProfile.getPortName() );
        
        // open the streams
        InputStream is = serialPort.getInputStream();
        InputStreamReader isr = new InputStreamReader(is);
        input = new BufferedReader(isr);

        // add event listeners
        serialPort.addEventListener(this);

        feedDataList = new ArrayList();
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

                FeedData feedData = FeedData.valueOf(inputLine);
                
                
                

                
                System.out.println(inputLine);
            } 
            catch (Exception e) 
            {
                System.err.println(e.toString());
            }
        }
    }    
}
