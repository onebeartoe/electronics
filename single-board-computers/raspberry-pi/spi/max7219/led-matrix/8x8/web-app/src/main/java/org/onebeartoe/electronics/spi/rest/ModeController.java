
package org.onebeartoe.electronics.spi.rest;

import org.onebeartoe.electronics.spi.DisplayModes;
import org.onebeartoe.electronics.spi.manager.SpiException;
import org.onebeartoe.electronics.spi.manager.SpiManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import static org.springframework.web.bind.annotation.RequestMethod.GET;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ModeController 
{
    private Logger logger = LoggerFactory.getLogger(this.getClass());
    
    private final SpiManager manager;
    
    public ModeController(SpiManager manager)
    {
        this.manager = manager;
    }

    @RequestMapping(value = "/api/mode/{mode}", method = GET)
    public String getCurrentMode(@PathVariable(required = true) String mode,
                                 @RequestParam(name="userText", required=false, 
                                               defaultValue="AINT-GOT-NO-TEXT") String userText) 
    {        
        System.out.println("userText: " + userText);

        var exceptionMessage = "";

        try 
        {
            var displayMode = DisplayModes.valueOf(mode);
            
            switch(displayMode)
            {
                case USER_TEXT:
                {
                    System.out.println("user text: " + userText);

                    manager.scrollUserText(userText); 
                    
                    break;
                }
                case WEATHER:
                {
                    var degrees = 78;
                    
                    var text = "Temp: " + degrees;
                    
                    manager.scrollUserText(text);
                    
                    break;
                }
                default: 
                {
                    exceptionMessage = " - " + displayMode + " is not ready!";
                    
                    System.err.println(exceptionMessage);
                }
            }
        } 
        catch (SpiException ex) 
        {
            logger.error(ex.getMessage(), ex);
        }
        
        return "Greetings, " + mode + " from Spring Boot!"  + exceptionMessage;
    }
}
