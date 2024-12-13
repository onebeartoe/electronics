
package org.onebeartoe.sht41.trinkey;


import static org.assertj.core.api.Assertions.*;

import org.testng.annotations.Test;

//import static org.onebeartoe.sht41.trinkey.SensorReadings.parseTwoDigitOneDecimal;

/**
 *
 */
public class SensorReadingsTest 
{    
    @Test
    public void parseLine_temperature_oneDigit()
    {
        var line = "Temperature 1.3 c";
        
        var reading = SensorReadings.parseLine(line);
        
        Float value = null;
        
        if(reading instanceof TemperatureReading r)
        {
            value = r.temperature();
        }
        
        assertThat(value).isEqualTo(1.3f);
    }
    
    @Test
    public void parseLIne_temperature_twoDigit()
    {
        var line = "Temperature 12.8 c";
        
        var reading = SensorReadings.parseLine(line);
        
        Float value = null;
        
        if(reading instanceof TemperatureReading r)
        {
            value = r.temperature();
        }
        
        assertThat(value).isEqualTo(12.8f);        
    }
    

    @Test
    public void parseLine_humidity_oneDigit()
    {
        var line = "Humidity 2.8 %";
        
        var reading = SensorReadings.parseLine(line);
        
        Float value = null;
        
        if(reading instanceof HumidityReading r)
        {
            value = r.humidity();
        }
        
        assertThat(value).isEqualTo(2.8f);
    }
    
    @Test
    public void parseLine_humidity_twoDigit()
    {
        var line = "Humidity 12.8 %";

        var reading = SensorReadings.parseLine(line);
        
        Float value = null;
        
        if(reading instanceof HumidityReading r)
        {
            value = r.humidity();
        }
        
        assertThat(value).isEqualTo(12.8f);        
    }
    
    @Test
    public void parseLine_badReading()
    {
        var line = "Temp: 20.2 c";
        
        var reading = SensorReadings.parseLine(line);
        
        assertThat(reading).isInstanceOf(BadReading.class);
    }
    
    @Test
    public void parseLine_badReading_blank()
    {
        var line = "\n \n";
        
        var reading = SensorReadings.parseLine(line);
        
        assertThat(reading).isInstanceOf(BadReading.class);        
    }

    @Test
    public void parseLine_badReading_badFormat()
    {
        var line = "\n__\n";
        
        var reading = SensorReadings.parseLine(line);
        
        assertThat(reading).isInstanceOf(BadReading.class);        
    }    
    
    @Test(expectedExceptions = {IllegalArgumentException.class})
    public void parseTwoDigitOneDecimal_badReading()
    {        
        SensorReadings.parseTwoDigitOneDecimal("dlkaj");
    }

    @Test(expectedExceptions = {IllegalArgumentException.class})
    public void parseTwoDigitOneDecimal_badReading_correctLength_butBadFormat()
    {        
        SensorReadings.parseTwoDigitOneDecimal("1.00");                
    }
    
    @Test(expectedExceptions = {IllegalArgumentException.class})
    public void parseTwoDigitOneDecimal_badReading_correctLength_blank()
    {        
        SensorReadings.parseTwoDigitOneDecimal("\t \n");
    }    
    
    @Test(expectedExceptions = {IllegalArgumentException.class})
    public void parseTwoDigitOneDecimal_badReading_tooLarge()
    {
        SensorReadings.parseTwoDigitOneDecimal("101.9");
    } 
        
    @Test(expectedExceptions = {IllegalArgumentException.class})
    public void parseTwoDigitOneDecimal_badReading_noDecimal()
    {
        SensorReadings.parseTwoDigitOneDecimal(".9");
    } 
   
    @Test
    public void parseTwoDigitOneDecimal_success_oneDigit()
    {        
        var actual = SensorReadings.parseTwoDigitOneDecimal("2.5");

        var expected = 2.5f;

        assertThat(actual).isEqualTo(expected);
    }    
   
    @Test
    public void parseTwoDigitOneDecimal_success_twoDigit()
    {
        var actual = SensorReadings.parseTwoDigitOneDecimal("82.3");

        var expected = 82.3f;

        assertThat(actual).isEqualTo(expected);
    }   
}
