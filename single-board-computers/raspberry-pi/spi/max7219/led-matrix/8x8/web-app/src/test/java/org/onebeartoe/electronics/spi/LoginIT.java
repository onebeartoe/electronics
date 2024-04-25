
package org.onebeartoe.electronics.spi;


import io.github.bonigarcia.wdm.WebDriverManager;
import java.util.concurrent.TimeUnit;
//import java.time.Duration;
import org.junit.jupiter.api.Test; 
import org.openqa.selenium.WebDriver; 
import org.openqa.selenium.chrome.ChromeDriver; 
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.springframework.boot.test.context.SpringBootTest;

import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.web.server.LocalServerPort;

/**
 *
 */
//@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class LoginIT 
{

//    @LocalServerPort
//    private int port;    

	@Test 
	public void testApp() 
	{
            var chromePath = "/usr/bin/google-chrome";
//            var firefoxPath = "/usr/bin/firefox";
            
            chromePath = "/home/roberto/Workspace/world/chromedriver/chrome-linux64-107/chromedriver";
        
//            chromePath = "/home/roberto/Workspace/world/chromedriver/chromedriver_linux64-114/chromedriver";
            
//            chromePath = "/home/roberto/Workspace/world/chromedriver/chrome-linux64-214/chrome";
            
//            chromePath = "/home/roberto/Workspace/world/chromedriver/chromedriver-linux64-214/chromedriver";

            chromePath = "/home/roberto/Versioning/owner/github/building-java-applications/web/automation/src/test/resources/chromedriver-2.37/chromedriver";

            var key = "webdriver.chrome.driver";
            
            System.setProperty(key, chromePath);
            
//            System.setProperty(key, firefoxPath);
            
//WebDriverManager.firefoxdriver().setup();
WebDriverManager.chromedriver().setup();            
            
                ChromeOptions chromeOptions = new ChromeOptions();
                chromeOptions.setBinary(chromePath);

//                chromeOptions.addArguments("--headless");
//                chromeOptions.addArguments("--no-sandbox");            
            
//		WebDriver driver = new FirefoxDriver();
//		WebDriver driver = new ChromeDriver(); 
		WebDriver driver = new ChromeDriver(chromeOptions); 

        driver.manage().timeouts().implicitlyWait(500, TimeUnit.MILLISECONDS); //Duration.ofMillis(500));


//                driver.navigate();
                 
		driver.get("https://www.google.com/"); 
//		driver.get("http://localhost:8080"); 

                
		// URL of your Spring Boot app 
		// Perform your test actions (e.g., click, input text) 
		driver.quit(); 
	}
}
