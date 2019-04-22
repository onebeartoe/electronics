
package org.onebeartoe.weather.station.relay;

import org.onebeartoe.application.AppletService;
import org.onebeartoe.application.RunProfile;

/**
 * This class provides methods to post sensor values to the Internet of Things
 * platform, AdafruitIO.
 * 
 * @author Roberto Marquez
 */
public class WeatherStationRelayService extends AppletService
{    
    public void serviceRequest(RunProfile runProfile)
    {
        // Alas, we have to cast.
        CliWeatherStationRelayRunProfile rp = (CliWeatherStationRelayRunProfile) runProfile;
        
        logger.info("termpeature is : 25C");        
    }
}
