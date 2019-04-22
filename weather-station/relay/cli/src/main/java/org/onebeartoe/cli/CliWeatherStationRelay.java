
package org.onebeartoe.cli;

import java.util.List;
import org.onebeartoe.application.CommandLineInterfaceApplet;
import org.onebeartoe.io.serial.SerialPorts;

/**
 * 
 * On Linux this command works with the RXTX provided by apt-get:
 *
 *      sudo apt-get install librxtx-java
 * 
 *      cd /usr/lib/jni/
 * 
 *      sudo ln -s librxtxSerial-2.2pre1.so rxtxSerial.so
 * 
 *      java -Djava.library.path=/usr/lib/jni/ -jar extreme-notifications-1.0-SNAPSHOT-jar-with-dependencies.jar /dev/ttyACM0 strip-job.mapping
 * 
 * @author Roberto Marquez
 */
public class CliWeatherStationRelay extends CommandLineInterfaceApplet
{
    public static void main(String [] args) throws Exception
    {   
       String key = "java.library.path";
       String libPath = System.getProperty(key);
       System.out.println();
       System.out.println("libPat:" + libPath);       
       
       List<String> ports = SerialPorts.list();
       
       System.out.println();
       System.out.println("serial ports:");
       
       ports.forEach(System.out::println);
       
       
        
       CommandLineInterfaceApplet app = new CliWeatherStationRelay();        
       app.execute(args);       
    }
}
