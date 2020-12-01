
package org.onebeartoe.electronics.spi.controller;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
public class InventoryListingController
{
    @RequestMapping("/products")
    public String index() 
    {
            return "<p>Product Listing</p>";
    }
}
