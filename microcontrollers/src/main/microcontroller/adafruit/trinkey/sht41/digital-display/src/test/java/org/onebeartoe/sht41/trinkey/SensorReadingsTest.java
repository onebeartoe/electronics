
package org.onebeartoe.sht41.trinkey;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import org.onebeartoe.sht41.trinkey.SensorReadings;

//import static org.onebeartoe.sht41.trinkey.SensorReadings.parseTwoDigitOneDecimal;

/**
 *
 * @author roberto
 */
public class SensorReadingsTest 
{
    
    public SensorReadingsTest() 
    {
        
    }
    
    @Test
    public void parseTwoDigitOneDecimal_badReading()
    {        
        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () ->
            SensorReadings.parseTwoDigitOneDecimal("dlkaj")
        );                
    }
    
    @Test
    public void parseTwoDigitOneDecimal_badReading_tooLarge()
    {
        IllegalArgumentException exception = assertThrows(IllegalArgumentException.class, () ->
            SensorReadings.parseTwoDigitOneDecimal("101.9")
        );
    } 
   
    @Test
    public void parseTwoDigitOneDecimal_success_oneDigit()
    {        
        var actual = SensorReadings.parseTwoDigitOneDecimal("2.5");

        var expected = 2.5f;

        assertEquals(expected, actual);
    }    
   
    @Test
    public void parseTwoDigitOneDecimal_success_twoDigit()
    {
        var actual = SensorReadings.parseTwoDigitOneDecimal("82.3");

        var expected = 82.3f;

        assertEquals(expected, actual);        
    }    
    
}
