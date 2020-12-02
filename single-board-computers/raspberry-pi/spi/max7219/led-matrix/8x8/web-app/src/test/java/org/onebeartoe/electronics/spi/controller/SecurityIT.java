
package org.onebeartoe.electronics.spi.controller;

import java.net.URI;
import java.net.URL;
import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.onebeartoe.electronics.spi.rest.ModeControlsIT.userName;
import static org.onebeartoe.electronics.spi.rest.ModeControlsIT.userPassword;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;
import org.springframework.http.ResponseEntity;


/**
 * AC5
 * 
 * These tests verify the API and content URLs have security/authentication enabled.
 */
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class SecurityIT 
{
    @LocalServerPort
    private int port;
    
    @Autowired
    private TestRestTemplate template;
    
    public URI setUp(String subpath) throws Exception 
    {
        String resource = "http://localhost:" + port + subpath;
        
        URL base = new URL(resource);
        
        return base.toURI();
    }    
    
    @Test()
    public void indexIsAvailable() throws Exception
    {
        URI resource = setUp("/");
        
        ResponseEntity<String> response = template.getForEntity(resource, String.class);
    
        String body = response.getBody();
        
        assertThat(body).contains("Welcome Here!");
    }
    
    @Test
    public void loginIsAvailable() throws Exception 
    {
        URI resource = setUp("/login");

        expectLoginPage(resource);
    }    
    
    @Test
    public void apisAreNotAvailable() throws Exception
    {
        URI resource = setUp("/api/mode");

        expectLoginPage(resource);
    }

    @Test
    public void contentIsNotAvailable() throws Exception
    {
        URI resource = setUp("/controls");
        
        expectLoginPage(resource);
    }
    
    private void expectLoginPage(URI resource)
    {
        ResponseEntity<String> response = template.getForEntity(resource, String.class);
    
        String body = response.getBody();
        
        // without logging in, expect the login page
        assertThat(body).contains("User Name:");
        assertThat(body).contains("Password:");
    }
}
