package org.onebeartoe.electronics.spi.controller;

import org.springframework.context.annotation.Configuration;
import org.springframework.core.annotation.Order;
import org.springframework.security.config.annotation.web.builders.WebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

/**
 * This class configures the test environment to not apply security to any API 
 * resources.  It basically undoes the security in WebSecurityConfiguration.java
 */
@Configuration()
@Order(value = 90)
public class ApplicationSecurity extends WebSecurityConfigurerAdapter
{
    @Override
    public void configure(WebSecurity web) throws Exception 
    {
        web.ignoring()
            .antMatchers("/**");
    }
}
