
package org.onebeartoe.electronics.spi.manager;

import be.webtechie.pi4jgpio.definition.AsciiCharacter;
import be.webtechie.pi4jgpio.definition.SpiCommand;
import be.webtechie.pi4jgpio.helper.AsciiCharacterMode;
import static be.webtechie.pi4jgpio.helper.AsciiCharacterMode.scrollAsciiCharacter;
import be.webtechie.pi4jgpio.helper.DemoMode;
import be.webtechie.pi4jgpio.helper.ImageMode;

import com.pi4j.io.spi.SpiChannel;
import com.pi4j.io.spi.SpiDevice;
import com.pi4j.io.spi.SpiFactory;

import java.io.IOException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.config.ConfigurableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

/**
 * This class provisions Serial Peripheral Interface (SPI) devices
 */
@Component
@Scope(value = ConfigurableBeanFactory.SCOPE_SINGLETON) // Default value, added for clarity
public class SpiManager 
{
    private Logger logger = LoggerFactory.getLogger(this.getClass());

    private SpiDevice spi;
    
    public SpiManager() throws IOException, InterruptedException
    {
        System.out.println("Starting SPI example...");

        try
        {
            // Initialize the SpiFactory
            spi = SpiFactory.getInstance(SpiChannel.CS0,
                    SpiDevice.DEFAULT_SPI_SPEED, // default spi speed 1 MHz
                    SpiDevice.DEFAULT_SPI_MODE); // default spi mode 0

            spi.write(SpiCommand.TEST.getValue(), (byte) 0x01);
            System.out.println("Test mode all on");
            Thread.sleep(1000);

            spi.write(SpiCommand.TEST.getValue(), (byte) 0x00);
            System.out.println("Test mode all off");
            Thread.sleep(1000);

            spi.write(SpiCommand.DECODE_MODE.getValue(), (byte) 0x00);
            System.out.println("Use all bits");

            spi.write(SpiCommand.BRIGHTNESS.getValue(), (byte) 0x08);
            System.out.println("Changed brightness to medium level"
                + " (0x00 lowest, 0x0F highest)");

            spi.write(SpiCommand.SCAN_LIMIT.getValue(), (byte) 0x0f);
            System.out.println("Configured to scan all digits");

            spi.write(SpiCommand.SHUTDOWN_MODE.getValue(), (byte) 0x01);
            System.out.println("Woke up the MAX7219, is off on startup");

            DemoMode.showRows(spi, 250);
            DemoMode.showCols(spi, 250);
            DemoMode.showRandomOutput(spi, 5, 500);

            ImageMode.showAllImages(spi, 2000);
            AsciiCharacterMode.showAllAsciiCharacters(spi, 750);
            AsciiCharacterMode.scrollAllAsciiCharacters(spi, 50);
        }
        catch(Exception e)
        {
            logger.error(e.getMessage(), e);
        }
    }
    
    /**
     * Scroll all the characters as defined in the user defined string.
     */
    public void scrollUserText(String text) throws SpiException
    {
        // Milliseconds between every column move
        int waitBetweenMove = 50;
        
        try 
        {
            char[] toCharArray = text.toCharArray();
            for(char ascii : toCharArray)
//            for (int ascii = 32; ascii <= 126; ascii++) 
            {
                AsciiCharacter asciiCharacter = AsciiCharacter.getByAscii(ascii);
                if (asciiCharacter != null) 
                {
                    scrollAsciiCharacter(spi, asciiCharacter, waitBetweenMove);
                    System.out.println("Scrolled : " + asciiCharacter.name());
                    Thread.sleep(250);
                }
            }
        } 
        catch (Exception ex) 
        {
            logger.error("Error during Ascii: " + ex.getMessage(), ex);
        }
    } 
}
