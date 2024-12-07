package org.onebeartoe.mavenproject1;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import java.io.BufferedInputStream;

//import gnu.io.SerialPort;
//import gnu.io.SerialPortEvent;
//import gnu.io.SerialPortEventListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.logging.Level;
//import java.lang.System.Logger;
import java.util.logging.Logger;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

//import org.onebeartoe.io.serial.SerialPorts;

/**
 * JavaFX App
 */
public class App extends Application //implements SerialPortEventListener
{
//    private SerialPort serialPort;
    
    private BufferedReader input;
    
    private Logger logger;

    @Override
    public void start(Stage stage) throws Exception 
    {
        logger = Logger.getLogger( getClass().getName() );
        
        var javaVersion = SystemInfo.javaVersion();
        
        var javafxVersion = SystemInfo.javafxVersion();

        var label = new Label("Hello, JavaFX " + javafxVersion + ", running on Java " + javaVersion + ".");
        
        var scene = new Scene(new StackPane(label), 640, 480);
        
        stage.setScene(scene);
        
        stage.show();
        
        var portName = "/dev/ttyACM0";
        
//        serialPort = SerialPorts.get( portName);
//        
//        // open the streams
//        InputStream is = serialPort.getInputStream();
//        InputStreamReader isr = new InputStreamReader(is);
//        input = new BufferedReader(isr);
//
//        // add event listeners
//        serialPort.addEventListener(this);        


//SerialPort.get

SerialPort comPort = SerialPort.getCommPorts()[0];
comPort.openPort();
comPort.addDataListener(new SerialPortDataListener() {
   @Override
   public int getListeningEvents() { return 
           SerialPort.LISTENING_EVENT_DATA_AVAILABLE; 
//           SerialPort.LISTENING_EVENT_DATA_RECEIVED;
   }
   
   @Override
   public 
           synchronized 
        void serialEvent(SerialPortEvent event) 
   {
      if (event.getEventType() != 
              SerialPort.LISTENING_EVENT_DATA_AVAILABLE
//              SerialPort.LISTENING_EVENT_DATA_RECEIVED
              )
      {
         return;
      }
      
//      byte[] newData = new byte[comPort.bytesAvailable()];
//      int numRead = comPort.readBytes(newData, newData.length);
//      System.out.println("Read " + numRead + " bytes.-. " + new String(newData));
      
      var instream = comPort.getInputStream();
      var buffStream = new BufferedReader( new InputStreamReader(instream) ) ;
       try {
          String line = buffStream.readLine();
           System.out.println("one = " + line);
          
//      System.out.println("Read " + numRead + " bytes.-. " + new String(newData));

       } catch (IOException ex) {
           Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, ex);
       }
   }
});
        
        
    }

    /**
     * Handle an event on the serial port. Read the data and print it.
     */
//    @Override
//    public synchronized void serialEvent(SerialPortEvent event) 
//    {
//        if(event.getEventType() == SerialPortEvent.DATA_AVAILABLE) 
//        {
//            try 
//            {
//                String inputLine = input.readLine();

//                feedData = FeedData.valueOf(inputLine);
              
//                System.out.println(inputLine);
//                System.out.println();
                
  //              boolean valid = isValid(feedData);
                
  //              if(valid)
//                {
    //                updateFeedDataList(feedData);
//                }
      //          else
//                {
//                    String message = "unknown topic was dropped >" + inputLine + "<" + "\n";
//                    
//                    logger.warning(message);
//                }
//            } 
//            catch (Exception e) 
//            {
//                System.err.println(e.toString());
//            }
//        }
//    }    
    
    public static void main(String[] args) {
        launch();
    }

    
}