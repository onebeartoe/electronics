
package org.onebeartoe.electronics.spi.controller;


import java.net.URL;
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

//TODO: is this test needed?
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class LoginControllerIT 
{
    @LocalServerPort
    private int port;

    private URL base;

    @Autowired
    private TestRestTemplate template;

    @BeforeEach
    public void setUp() throws Exception 
    {
        this.base = new URL("http://localhost:" + port + "/login");
    }

    @Test
    public void getHello() throws Exception 
    {
        ResponseEntity<String> response = template.withBasicAuth(userName, userPassword)
                .getForEntity(base.toString(), String.class);

        String body = response.getBody();
        
        assertTrue(body.contains("User Name:"));
        assertTrue(body.contains("Password:"));
    }
}
