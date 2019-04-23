
package org.onebeartoe.weather.station.relay;

import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.RunProfile;
import org.onebeartoe.system.Sleeper;

/**
 * This class provides methods to post sensor values to the Internet of Things
 * platform, AdafruitIO.
 * 
 * @author Roberto Marquez
 */
public class WeatherStationRelayService extends AppletService
{    
    private final long SIX_SECONDS = 1000 * 6;

    private final long SIXTY_SECONDS = 1000 * 60;
    
    private long postInterval = SIX_SECONDS;
    
    public void serviceRequest(RunProfile runProfile)
    {
        // Alas, we have to cast.
        CliWeatherStationRelayRunProfile rp = (CliWeatherStationRelayRunProfile) runProfile;
        
        rp.setRelayStatus(RelayStatus.RUNNING);
        
        Thread relayThread = new Thread(() ->
        {
            logger.info("running dameon code" + "\n");
            
            while( rp.getRelayStatus() == RelayStatus.RUNNING)
            {                
                Sleeper.sleepo(postInterval);
                
                logger.info("termpeature is : 225C" + "\n");
                
                
            }
        });
        
//        relayThread.setDaemon(true);        
        relayThread.start();
    }
}
