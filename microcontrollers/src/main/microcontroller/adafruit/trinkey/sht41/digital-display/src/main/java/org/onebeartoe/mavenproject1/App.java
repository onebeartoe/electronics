package org.onebeartoe.mavenproject1;

import be.webtechie.javafxlednumberdisplay.component.LedNumber;
import be.webtechie.javafxlednumberdisplay.definition.DisplaySkin;
import be.webtechie.javafxlednumberdisplay.definition.HighlightType;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.logging.Level;

import java.util.logging.Logger;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.Separator;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

/**
 * Demo app with digitial display for the Adafruit SHT41 Trinkey
 */
public class App extends Application implements SerialPortDataListener
{

    private BufferedReader input;

    private Logger logger;
    
    private SerialPort comPort;

    @Override
    public void start(Stage stage) throws Exception {
        logger = Logger.getLogger(getClass().getName());

        var javaVersion = SystemInfo.javaVersion();
        var javafxVersion = SystemInfo.javafxVersion();        
        var versionsMessage = "Hello, JavaFX " + javafxVersion + ", running on Java " + javaVersion + ".";
        System.out.println(versionsMessage);
        
        var temperatureLabel = new Label("Temperature");
        LedNumber ledNumber = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED);
        HBox temperatureHBox = new HBox();
        temperatureHBox.setSpacing(10);
        temperatureHBox.setAlignment(Pos.CENTER);        
        temperatureHBox.getChildren().addAll(
                temperatureLabel, 
                ledNumber,
                    new Label("c"));

 
        LedNumber humidityNumber = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED);
        HBox humidityHBox = new HBox();
        humidityHBox.setSpacing(10);
        humidityHBox.setAlignment(Pos.CENTER);        
        humidityHBox.getChildren().addAll( new Label("Humidity"),
                                    humidityNumber,
                                    new Label("%"));
        
        var separator = new Separator();
        var style = """
                    .Separator .line {
                        -fx-border-color: #e79423;
                        -fx-border-width: 2;    
                    }
        """;
//        var style = "-fx-border-color:#D2691E; -fx-border-width:2";
        
        separator.setStyle(style);
        var mainVbox = new VBox();
        mainVbox.setSpacing(25);
        mainVbox.setPadding(new Insets(10));
        mainVbox.getChildren().addAll(temperatureHBox,
                        separator,
                        humidityHBox);
        
        var scene = new Scene(mainVbox, 640, 480);
//        var scene = new Scene(new StackPane(temperatureHBox), 640, 480);

        stage.setScene(scene);

        stage.show();
        
ledNumber.highlight(HighlightType.FOUR.FOUR);        

// the SHT41 Trinkey appears as this port name        
//        var portName = "/dev/ttyACM0";
        comPort = SerialPort.getCommPorts()[0];
        comPort.openPort();
//ADD this BACK!!!!!!        
//        comPort.addDataListener(this);
    }

    @Override
    public int getListeningEvents() {
                return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
//           SerialPort.LISTENING_EVENT_DATA_RECEIVED;
    }

    @Override
    public synchronized void serialEvent(SerialPortEvent event) 
    {
                if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) 
                {
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
    
    public static void main(String[] args) 
    {
        launch();
    }
}
