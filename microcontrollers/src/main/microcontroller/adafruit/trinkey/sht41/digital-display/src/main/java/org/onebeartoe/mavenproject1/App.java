package org.onebeartoe.mavenproject1;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;

import java.util.logging.Logger;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

/**
 * Demo app with digitial display for the Adafruit SHT41 Trinkey
 */
public class App extends Application //implements SerialPortEventListener
{

    private BufferedReader input;

    private Logger logger;

    @Override
    public void start(Stage stage) throws Exception {
        logger = Logger.getLogger(getClass().getName());

        var javaVersion = SystemInfo.javaVersion();

        var javafxVersion = SystemInfo.javafxVersion();
        
        var label = new Label("Hello, JavaFX " + javafxVersion + ", running on Java " + javaVersion + ".");

        var scene = new Scene(new StackPane(label), 640, 480);

        stage.setScene(scene);

        stage.show();

// the SHT41 Trinkey appears as this port name        
//        var portName = "/dev/ttyACM0";
        SerialPort comPort = SerialPort.getCommPorts()[0];
        comPort.openPort();
        comPort.addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
//           SerialPort.LISTENING_EVENT_DATA_RECEIVED;
            }

            @Override
            public synchronized void serialEvent(SerialPortEvent event) {
                if (event.getEventType()
                        != SerialPort.LISTENING_EVENT_DATA_AVAILABLE //              SerialPort.LISTENING_EVENT_DATA_RECEIVED
                        ) {
                    return;
                }

//      byte[] newData = new byte[comPort.bytesAvailable()];
//      int numRead = comPort.readBytes(newData, newData.length);
//      System.out.println("Read " + numRead + " bytes.-. " + new String(newData));
                var instream = comPort.getInputStream();
                var buffStream = new BufferedReader(new InputStreamReader(instream));
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

    public static void main(String[] args) 
    {
        launch();
    }
}
