
package org.onebeartoe.electronics.spi.rest;

import static org.assertj.core.api.Assertions.*;

import java.net.URL;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;
import org.springframework.http.ResponseEntity;

//TODO: change the name to something meaningful
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class InventoryListingIT 
{
    private Logger logger = LoggerFactory.getLogger(this.getClass());
    
    @LocalServerPort
    private int port;

    private URL base;

    @Autowired
    private TestRestTemplate template;

    @BeforeEach
    public void setUp() throws Exception 
    {
        this.base = new URL("http://localhost:" + port + "/products");
    }

    @Test
    public void productsAreListed() throws Exception 
    {
        String path = base.toString();
        System.out.println("path = " + path);
        System.out.println("tmplate = " + template);
        ResponseEntity<String> response = template.getForEntity(path,
                String.class);
        
        String body = response.getBody();
        
        logger.debug("body = " + body);        
        
//TODO: update the string check for something acutally on the page
        assertThat(body).contains("Product Listing");
    }
}
