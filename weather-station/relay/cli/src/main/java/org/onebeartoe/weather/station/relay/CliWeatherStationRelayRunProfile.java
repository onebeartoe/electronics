
package org.onebeartoe.weather.station.relay;

import java.util.ArrayList;
import java.util.List;
import org.onebeartoe.application.RunProfile;
import org.onebeartoe.web.adafruit.io.FeedData;

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
    
    private List<FeedData> feedDataList;
    
    public CliWeatherStationRelayRunProfile()
    {
        feedDataList = new ArrayList();
    }

    public List<FeedData> getFeedDataList()
    {
        return feedDataList;
    }

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

    public void setFeedDataList(List<FeedData> feedDataList)
    {
        this.feedDataList = feedDataList;
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
