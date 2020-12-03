
package org.onebeartoe.electronics.spi.rest;

import org.onebeartoe.electronics.spi.manager.SpiException;
import org.onebeartoe.electronics.spi.manager.SpiManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.slf4j.event.Level;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import static org.springframework.web.bind.annotation.RequestMethod.GET;

@RestController
public class ModeController 
{
    private Logger logger = LoggerFactory.getLogger(this.getClass());
    
    private final SpiManager manager;
    
    public ModeController(SpiManager manager)
    {
        this.manager = manager;
        
        System.out.println("manager = " + this.manager);
    }

    
//TODO: make this a POST!!!
//TODO:     NO, make this its own GET an have the update be a separate POST.      
    @RequestMapping(value = "/api/mode", method = GET)
//    @RequestMapping(value = "/api/mode", method = POST)
    public String getCurrentMode() 
    {
        try 
        {
            String text = "BEST AT BAT";
            
            manager.scrollUserText(text);
        } 
        catch (SpiException ex) 
        {
            logger.error(ex.getMessage(), ex);
        }
        
        return "Greetings from Spring Boot!";
    }
}
