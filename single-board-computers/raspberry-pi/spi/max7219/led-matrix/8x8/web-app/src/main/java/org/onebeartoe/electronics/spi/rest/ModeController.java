
package org.onebeartoe.electronics.spi.rest;

import java.util.logging.Level;
import java.util.logging.Logger;
import org.onebeartoe.electronics.spi.manager.SpiException;
import org.onebeartoe.electronics.spi.manager.SpiManager;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class ModeController 
{
    private final SpiManager manager;
    
    public ModeController(SpiManager manager)
    {
        this.manager = manager;
        
        System.out.println("manager = " + this.manager);
    }

    @RequestMapping("/api/mode")
    public String index() 
    {
        try 
        {
            manager.scrollUserText();
        } 
        catch (SpiException ex) 
        {
            Logger.getLogger(ModeController.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return "Greetings from Spring Boot!";
    }
}
