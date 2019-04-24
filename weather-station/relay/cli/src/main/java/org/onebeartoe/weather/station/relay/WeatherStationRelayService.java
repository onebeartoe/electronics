
package org.onebeartoe.weather.station.relay;

import java.io.IOException;
import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.RunProfile;
import org.onebeartoe.system.Sleeper;
import org.onebeartoe.web.adafruit.io.AdafruitIoService;
import org.onebeartoe.web.adafruit.io.AioResponse;
import org.onebeartoe.web.adafruit.io.ApacheAdafruitIoService;

/**
 * This class provides methods to post sensor values to the Internet of Things
 * platform, AdafruitIO.
 * 
 * @author Roberto Marquez
 */
public class WeatherStationRelayService extends AppletService
{    
    private final long SIX_SECONDS = 1000 * 6;

    private final long FIFTEEN_SECONDS = 1000 * 15;
    
    private final long SIXTY_SECONDS = 1000 * 60;
    
    private long postInterval = FIFTEEN_SECONDS;
    
    private AdafruitIoService iotService;
    
    private WeatherStationSerialListener serialListener;
    
//    public WeatherStationRelayService(CliWeatherStationRelayRunProfile runProfile)
//    {
//
//    }
    
    public void serviceRequest(RunProfile runProfile)
    {
        // Alas, we have to cast.
        CliWeatherStationRelayRunProfile rp = (CliWeatherStationRelayRunProfile) runProfile;
        
        rp.setRelayStatus(RelayStatus.RUNNING);                

        String aioKey = rp.getIotKey();        
        iotService = new ApacheAdafruitIoService(aioKey);
        
        try
        {
            serialListener = new WeatherStationSerialListener(rp);
            
            Thread relayThread = new Thread(() ->
            {
                logger.info("running dameon code" + "\n");

                while( rp.getRelayStatus() == RelayStatus.RUNNING)
                {                
                    Sleeper.sleepo(postInterval);

                    logger.info("uploading to the Internet of Things platform..." + "\n");

                    String feedName = "sure";
                    
                    String value = "sure-value;";
                    
                    try
                    {
                        AioResponse ar = iotService.addFeedData(feedName, value);
                        
                        // we expect 201 response if the data was added to the feed
                        boolean failed = ar.code != 201;
                        
                        if(failed)
                        {
                            String message = "the request failed: " + ar.code + " - " + ar.content;
                            
                            logger.severe(message);
                        }
                    } 
                    catch (IOException ex)
                    {
                        String message = ex.getMessage();
                        
                        logger.severe(message);
                    }
                    
                    logger.info("TODO: upload to IoT platform" + "\n");
                }

                logger.info("shutting down dameon code" + "\n");

                if( serialListener != null)
                {
                    serialListener.closeSerialPort();
                }
            });

            relayThread.start();            
        } 
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }
}
