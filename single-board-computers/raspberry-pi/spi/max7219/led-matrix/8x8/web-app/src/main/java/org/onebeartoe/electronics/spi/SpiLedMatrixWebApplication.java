
package org.onebeartoe.electronics.spi;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.builder.SpringApplicationBuilder;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;

@SpringBootApplication
public class SpiLedMatrixWebApplication extends SpringBootServletInitializer
{
    @Override 
    protected SpringApplicationBuilder configure(SpringApplicationBuilder application)
    {
        return application.sources(SpiLedMatrixWebApplication.class);
    }
    
    public static void main(String[] args) 
    {
        SpringApplication.run(SpiLedMatrixWebApplication.class, args);
    }
}
