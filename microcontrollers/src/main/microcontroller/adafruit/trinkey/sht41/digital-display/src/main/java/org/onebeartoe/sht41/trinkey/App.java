package org.onebeartoe.sht41.trinkey;

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
import javafx.scene.text.Font;
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
    public void init()
    {
        
    }

    @Override
    public void start(Stage stage) throws Exception 
    {
        logger = Logger.getLogger(getClass().getName());

        var javaVersion = SystemInfo.javaVersion();
        var javafxVersion = SystemInfo.javafxVersion();        
        var versionsMessage = "JavaFX " + javafxVersion + " is running on Java " + javaVersion + ".";
        System.out.println(versionsMessage);
        
        var temperatureLabel = new Label("Temperature");
        var fontSize = 48.0f;
        var labelFont = new Font(fontSize);
//        temperatureLabel.setStyle("-fx-border-color:#D2691E; -fx-border-width:2; font-size:80;");
        temperatureLabel.setFont(labelFont);
        var hideDot = false;
        var temperatureTensLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        var temperatureOnesLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED);
        var temperatureTenthsLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        HBox temperatureHBox = new HBox();
        temperatureHBox.setSpacing(10);
        temperatureHBox.setAlignment(Pos.CENTER);        
        temperatureHBox.getChildren().addAll(temperatureLabel, 
                temperatureTensLed,
                    temperatureOnesLed,
                    temperatureTenthsLed,
                    new Label("c"));

        var humidityLabel = new Label("       Humidity");
        humidityLabel.setFont(labelFont);
        var humidityTensLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        var humidityOnesLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED);
        var humidityTenthsLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        var percentLabel = new Label("%");
        percentLabel.setFont(labelFont);
        HBox humidityHBox = new HBox();
        humidityHBox.setSpacing(10);
        humidityHBox.setAlignment(Pos.CENTER);        
        humidityHBox.getChildren().addAll(humidityLabel,
                                    humidityTensLed,
                                    humidityOnesLed,
                                    humidityTenthsLed,
                                    percentLabel);
        humidityHBox.setStyle("-fx-border-color:#D2691E; -fx-border-width:2; font-size:LARGE");
        
        var separator = new Separator();
//        var style = """
//                    .Separator .line {
//                        -fx-border-color: #e79423;
//                        -fx-border-width: 2;    
//                    }
//        """;
        var style = "-fx-border-color:#D2691E; -fx-border-width:2";
        
        separator.setStyle(style);
        var mainVbox = new VBox();
        mainVbox.setSpacing(25);
        mainVbox.setPadding(new Insets(10));
        mainVbox.getChildren().addAll(temperatureHBox,
                        separator,
                        humidityHBox);
        mainVbox.setStyle("-fx-background-color: grey;");
        
        var scene = new Scene(mainVbox, 640, 480);
        

        stage.setScene(scene);

        stage.show();
        
temperatureTensLed.highlight(HighlightType.FOUR.FOUR);        

        // the SHT41 Trinkey appears as this port name        
        var portName = "/dev/ttyACM0";
        comPort = SerialPort.getCommPorts()[0];
        comPort.openPort();
//ADD this BACK!!!!!!        
        comPort.addDataListener(this);
    }

    @Override
    public int getListeningEvents() 
    {
        return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
    }

    @Override
    public synchronized void serialEvent(SerialPortEvent event) 
    {
        if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) 
        {
            return;
        }

        var instream = comPort.getInputStream();
        var buffStream = new BufferedReader(new InputStreamReader(instream));
        try 
        {
            String line = buffStream.readLine();
            System.out.println("one = " + line);
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, ex);
        }
    }    
    
    public static void main(String[] args) 
    {
        launch();
    }
}
