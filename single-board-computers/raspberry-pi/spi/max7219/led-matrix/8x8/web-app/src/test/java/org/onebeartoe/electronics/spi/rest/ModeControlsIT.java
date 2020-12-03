//TODO: move this to .controller
package org.onebeartoe.electronics.spi.rest;

import static org.assertj.core.api.Assertions.*;

import java.net.URL;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.onebeartoe.electronics.spi.SpiLedMatrixWebApplication;
import org.onebeartoe.electronics.spi.controller.ApplicationSecurity;

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
public class ModeControlsIT 
{
    public static final String userName = "spi";
    public static final String userPassword = "matrix";
    
    @LocalServerPort
    private int port;

    private URL base;

//TODO: see if this can be re-instated
//    @Autowired
//    private TestRestTemplate template;

    @BeforeEach
    public void setUp() throws Exception 
    {
        this.base = new URL("http://localhost:" + port + "/controls");
    }

    /**
     * AC2
     * This integration test verifies all mode options are present on the user 
     * interface.
     * 
     * @throws Exception 
     */
    @Test
    public void modesArePresent() throws Exception 
    {
        Map<String, String> request = new HashMap<String, String>();
    request.put("username", userName);
    request.put("password", userPassword);
    request.put("grant_type", "password");
  
    TestRestTemplate template = new TestRestTemplate(userName, 
  userPassword, TestRestTemplate.HttpClientOption.ENABLE_COOKIES);
//    TestRestTemplate template = new TestRestTemplate(userName, userPassword);

//RestTemplateBuilder restTemplateBuilder = new RestTemplateBuilder();
//restTemplateBuilder.configure(template);
//TestRestTemplate testRestTemplate = new TestRestTemplate(restTemplateBuilder);


        ResponseEntity<String> response = template
                .withBasicAuth(userName, userPassword)
//                                            .postForEntity(base.toString(),request,String.class
                                            .getForEntity(base.toString(), String.class
                                            );
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
