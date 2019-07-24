/*
 */
package org.onebeartoe;

import java.util.Date;
import org.testng.annotations.Test;

/**
 *
 * @author Roberto Marquez
 */
public class DateTest
{
    @Test
    public void testDate()
    {
        Date d = new Date();
        
        int date = d.getDate();
                
        System.out.println("date: " + date);
    }
}
