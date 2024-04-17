
package org.onebeartoe.electronics.spi.rest;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

//TODO: remove this if it not used!!!!!!

@RestController
@Deprecated
public class InventoryListingController
{
    private Logger logger = LoggerFactory.getLogger(this.getClass());
    
    @RequestMapping("/products")
    public String index() 
    {
            return "<p>Product Listing</p>";
    }
}
