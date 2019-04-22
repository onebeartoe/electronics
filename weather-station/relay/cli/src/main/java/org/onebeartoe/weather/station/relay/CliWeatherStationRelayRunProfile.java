
package org.onebeartoe.weather.station.relay;

import org.onebeartoe.application.RunProfile;

/**
 *
 * @author Roberto Marquez
 */
public class CliWeatherStationRelayRunProfile extends RunProfile
{
    private String libraryPath;
    
    private String propertiesPath;
    
    public String getLibraryPath()
    {
        return libraryPath;
    }

    public String getPropertiesPath()
    {
        return propertiesPath;
    }
    
    public void setLibraryPath(String libraryPath)
    {
        this.libraryPath = libraryPath;
    }    

    public void setPropertiesPath(String propertiesPath)
    {
        this.propertiesPath = propertiesPath;
    }    
}
