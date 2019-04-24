
package org.onebeartoe.weather.station.relay;

import java.io.IOException;
import java.util.List;
import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.RunProfile;
import org.onebeartoe.system.Sleeper;
import org.onebeartoe.web.adafruit.io.AdafruitIoService;
import org.onebeartoe.web.adafruit.io.AioResponse;
import org.onebeartoe.web.adafruit.io.ApacheAdafruitIoService;
import org.onebeartoe.web.adafruit.io.FeedData;

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
    
    private long postInterval = SIXTY_SECONDS;
    
    private AdafruitIoService iotService;
    
    private WeatherStationSerialListener serialListener;

    private void sendDataFeed(CliWeatherStationRelayRunProfile runProfile)
    {
        List<FeedData> feedDataList = runProfile.getFeedDataList();
        
        for(FeedData feedData : feedDataList)
        {
            sendOneFeedData(feedData);
        }
    }
    
    private void sendOneFeedData(FeedData feedData)
    {
        logger.info("uploading to the Internet of Things platform..." + "\n");
                    
        String feedName = feedData.getTopic();

        String value = feedData.getValue();

        try
        {
            AioResponse ar = iotService.addFeedData(feedName, value);

            // we expect 201 response if the data was added to the feed
            boolean success = ar.code == 201;

            if(success)
            {
                logger.info("upload to IoT platform was successful" + "\n");
            }
            else
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
    }
    
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

                    sendDataFeed(rp);
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
