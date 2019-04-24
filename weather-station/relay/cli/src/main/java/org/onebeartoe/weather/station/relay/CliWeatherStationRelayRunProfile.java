
package org.onebeartoe.weather.station.relay;

import org.onebeartoe.application.RunProfile;

/**
 *
 * @author Roberto Marquez
 */
public class CliWeatherStationRelayRunProfile extends RunProfile
{
    private String iotKey;

    private String libraryPath;
    
    private String portName;
    
    private String propertiesPath;
    
    private RelayStatus relayStatus;

    public String getIotKey()
    {
        return iotKey;
    }
    
    public String getLibraryPath()
    {
        return libraryPath;
    }

    public String getPortName()
    {
        return portName;
    }
    
    public String getPropertiesPath()
    {
        return propertiesPath;
    }

    public RelayStatus getRelayStatus()
    {
        return relayStatus;
    }

    public void setIotKey(String iotKey)
    {
        this.iotKey = iotKey;
    }
    
    public void setLibraryPath(String libraryPath)
    {
        this.libraryPath = libraryPath;
    }

    public void setPortName(String portName)
    {
        this.portName = portName;
    }

    public void setPropertiesPath(String propertiesPath)
    {
        this.propertiesPath = propertiesPath;
    }

    public void setRelayStatus(RelayStatus relayStatus)
    {
        this.relayStatus = relayStatus;
    }
}
