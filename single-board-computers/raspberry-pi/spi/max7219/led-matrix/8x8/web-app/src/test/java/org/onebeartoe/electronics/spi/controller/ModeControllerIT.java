//TODO: move this to .rest
//          Yeah!!!
package org.onebeartoe.electronics.spi.controller;

import static org.assertj.core.api.Assertions.*;

import java.net.URL;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.onebeartoe.electronics.spi.SpiLedMatrixWebApplication;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;
import org.springframework.http.ResponseEntity;

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT,
        classes = 
        {
            ApplicationSecurity.class,         // include this class to override security
            SpiLedMatrixWebApplication.class
        })
public class ModeControllerIT 
{
    @LocalServerPort
    private int port;

    private URL base;

    @Autowired
    private TestRestTemplate template;

    @BeforeEach
    public void setUp() throws Exception 
    {
        this.base = new URL("http://localhost:" + port + "/api/mode/WEATHER");
    }

//TODO: give this a better name    
    @Test()
    public void getHello() throws Exception 
    {
        ResponseEntity<String> response = template
                .getForEntity(base.toString(), String.class);
    
        assertThat(response.getBody()).isEqualTo("Greetings, WEATHER from Spring Boot!");
    }
}
