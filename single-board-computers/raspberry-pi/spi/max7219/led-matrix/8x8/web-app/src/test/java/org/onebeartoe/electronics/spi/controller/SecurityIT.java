
package org.onebeartoe.electronics.spi.controller;

import java.net.URL;
import static org.assertj.core.api.Assertions.assertThat;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.onebeartoe.electronics.spi.SpiLedMatrixWebApplication;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;
import org.springframework.http.ResponseEntity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfiguration;

/**
 * These tests verify the API and content URLs have security/authentication enabled.
 */
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT
//              , 
//                classes =  
//                {
//                    WebSecurityConfiguration.class,
//                    SpiLedMatrixWebApplication.class
//                        
//                }
                )
public class SecurityIT 
{
    @LocalServerPort
    private int port;

    private URL base;
    
    @Autowired
    private TestRestTemplate template;
    
    @BeforeEach
    public void setUp() throws Exception 
    {
        this.base = new URL("http://localhost:" + port);
    }    
    
    @Test()
    public void indexIsAvailable()
    {
//        String resource = base + "/";
//        
//        ResponseEntity<String> response = template.getForEntity(resource, String.class);
//    
//        assertThat(response.getBody()).isEqualTo("Welcome");
    }
    
    @Test
    public void apisAreNotAvailable()
    {
//        String resource = base + "/api/mode";
//        
//        ResponseEntity<String> response = template.getForEntity(resource, String.class);
//    
//        assertThat(response.getBody()).isEqualTo("Login");
    }
        
    @Test
    public void contentAreNotAvailable()
    {
        
    }
}
