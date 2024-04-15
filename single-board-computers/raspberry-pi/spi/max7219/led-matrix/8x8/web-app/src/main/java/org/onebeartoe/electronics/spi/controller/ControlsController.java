
package org.onebeartoe.electronics.spi.controller;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

/**
 * This class sends an HTML UI for the products listing page.
 */
@Controller
public class ControlsController
{
    private Logger logger = LoggerFactory.getLogger(this.getClass());
    
    @Value("${title}")
    private String title;
    
    @GetMapping("/controls")
    public String products(@RequestParam(name="name", required=false, defaultValue="World") String name, Model model)  
    {
        model.addAttribute("name", name);

        model.addAttribute("title", title);

        return "controls";        
    }
}
