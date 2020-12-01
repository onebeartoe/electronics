
package org.onebeartoe.electronics.spi.rest;

import static org.assertj.core.api.Assertions.*;

import java.net.URL;
import java.util.List;
import java.util.stream.Collectors;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;
import org.springframework.http.ResponseEntity;

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class ModeControlsIT 
{
    @LocalServerPort
    private int port;

    private URL base;

    @Autowired
    private TestRestTemplate template;

    @BeforeEach
    public void setUp() throws Exception 
    {
        this.base = new URL("http://localhost:" + port + "/controls");
    }

    /**
     * AC4
     * This integration test verifies all mode options are present on the user 
     * interface.
     * @throws Exception 
     */
    @Test
    public void modesArePresent() throws Exception 
    {
        ResponseEntity<String> response = template.getForEntity(base.toString(),
                String.class);
        String body = response.getBody();
        assertThat(body).contains("New Product");

        Document doc = Jsoup.parse(body);
        Element modesSelect = doc.getElementById("modeOptions");
        Elements listItems = modesSelect.getElementsByTag("option");
        
        List<String> presentModes = listItems.stream()
                                        .map( item ->
                                        {
                                            String value = item.val();
                                            
                                            return value;
                                        })
                .collect( Collectors.toList());
        
        List<String> requiredModes = List.of("WEATHER", "USER_TEXT", "TIME", "ROTATE");
        
        for(String required : requiredModes)
        {
            // verify every required mode is present
            assertTrue( presentModes.contains(required) );
        }
    }
}
