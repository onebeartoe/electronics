
package org.onebeartoe.sht41.trinkey;

/**
 *
 */
public class SensorReadings 
{
    private SensorReadings()
    {
        
    }

    public static SensorReading parseLine(String line) 
    {
        SensorReading reading;
        
        if(line == null || line.isBlank())
        {
            reading = new BadReading(line);
        }
        else
        {
            String [] split = line.split("\\s+");  // split by whitespace 
            
            if(split.length != 3)
            {
                reading = new BadReading(line);
            }
            else if(line.startsWith("Temperature ") && line.endsWith("c"))
            {
                var s = split[1];

                float temp = Float.parseFloat(s);                    

                reading = new TemperatureReading(temp);
            }
            else if(line.startsWith("Humidity ") && line.endsWith("%"))
            {
                var s = split[1];

                var humidity = Float.valueOf(s);                    

                reading = new HumidityReading(humidity);
            }
            else
            {
                reading = new BadReading(line);
            }
        }

        return reading;
    }
    
    /**
     * Ths method verifies the text passed is in this format:
     * 
     *      one or two values before the decimal point and one value after
     * 
     * Valid Examples:
     * 
     *          99.8
     *           5.0
     * 
     * Invalid Examples:
     * 
     *          .8
     *       115.0
     *        20.78
     * 
     * @param text
     * @return 
     */
    public static float parseTwoDigitOneDecimal(String text)
    {
        if(text == null || text.isBlank())
        {
            throw new IllegalArgumentException("no value provided: " + text);
        }
        else if(text.length() != 3
                && text.length() != 4)
        {
            throw new IllegalArgumentException("length does not meet format: " + text.length());
        }
        
        var regularExpression = "^\\d{1,2}(\\.\\d{1})?$";
        
        float value;
        
        if(text.matches(regularExpression))
        {
            value = Float.valueOf(text);
        }
        else
        {
            var message = "text >" + text + "< does match xy.z format";
            
            throw new IllegalArgumentException(message);
        }
        
        return value;        
    }
}
