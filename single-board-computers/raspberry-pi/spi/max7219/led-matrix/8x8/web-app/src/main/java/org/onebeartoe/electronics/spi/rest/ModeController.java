
package org.onebeartoe.electronics.spi.rest;

import java.util.logging.Level;
import java.util.logging.Logger;
import org.onebeartoe.electronics.spi.manager.SpiException;
import org.onebeartoe.electronics.spi.manager.SpiManager;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import static org.springframework.web.bind.annotation.RequestMethod.GET;

@RestController
public class ModeController 
{
    private final SpiManager manager;
    
    public ModeController(SpiManager manager)
    {
        this.manager = manager;
        
        System.out.println("manager = " + this.manager);
    }

    
//TODO: make this a POST!!!    
    @RequestMapping(value = "/api/mode", method = GET)
//    @RequestMapping(value = "/api/mode", method = POST)
    public String index() 
    {
        try 
        {
            String text = "BEST AT BAT";
            
            manager.scrollUserText(text);
        } 
        catch (SpiException ex) 
        {
            Logger.getLogger(ModeController.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return "Greetings from Spring Boot!";
    }
}
