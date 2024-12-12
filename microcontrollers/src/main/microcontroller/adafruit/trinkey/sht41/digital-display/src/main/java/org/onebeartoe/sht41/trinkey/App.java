package org.onebeartoe.sht41.trinkey;

import be.webtechie.javafxlednumberdisplay.component.LedNumber;
import be.webtechie.javafxlednumberdisplay.definition.DisplaySkin;
import be.webtechie.javafxlednumberdisplay.definition.HighlightType;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import com.fazecast.jSerialComm.SerialPortTimeoutException;

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
    
    private LedNumber temperatureTensLed;
    
    private SerialPort comPort;
    
    @Override
    public void init()
    {
        temperatureTensLed = initializeLedNumber();
    }

    @Override
    public void start(Stage stage) throws Exception 
    {
        logger = Logger.getLogger(getClass().getName());

        var javaVersion = SystemInfo.javaVersion();
        var javafxVersion = SystemInfo.javafxVersion();        
        var versionsMessage = "JavaFX " + javafxVersion + " is running on Java " + javaVersion + ".";
        System.out.println(versionsMessage);
        
        var temperatureLabel = initializeLabel("Temperature");
        var hideDot = false;
        
        var temperatureOnesLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED);
        var temperatureTenthsLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        HBox temperatureHBox = new HBox();
        temperatureHBox.setSpacing(10);
        temperatureHBox.setAlignment(Pos.CENTER);        
        temperatureHBox.getChildren().addAll(temperatureLabel, 
                temperatureTensLed,
                    temperatureOnesLed,
                    temperatureTenthsLed,
                    initializeLabel("c"));

        var humidityLabel = initializeLabel("       Humidity");
        var humidityTensLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        var humidityOnesLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED);
        var humidityTenthsLed = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, hideDot);
        var percentLabel = initializeLabel("%");
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

        try 
        {
            var buffStream = new BufferedReader(new InputStreamReader(instream));            

            String line = buffStream.readLine();

            System.out.println("one = " + line);
        } 
        catch (IOException  ex) 
        {
            var message = ex.getMessage();

            logger.log(Level.SEVERE, message, ex);
        }
//        catch (SerialPortTimeoutException  ex) 
//        {
//            var message = ex.getMessage();
//
//            logger.log(Level.SEVERE, message, ex);
//        }
    }    
    
    private Label initializeLabel(String text)
    {
        var label = new Label(text);
        
        var fontSize = 48.0f;
        
        var labelFont = new Font(fontSize);      
        
        label.setFont(labelFont);
        
        label.setTextFill(Color.WHITE);        
        
        return label;
    }
    
    private LedNumber initializeLedNumber()
    {
        var showDot = false;
        
        return initializeLedNumber(showDot);
    }
    
    private LedNumber initializeLedNumber(boolean showDot)
    {
        var ledNumber = new LedNumber(DisplaySkin.CLASSIC, Color.BLUEVIOLET, Color.DARKGRAY, Color.RED, showDot);
               
        return ledNumber;
    }    
    
    public static void main(String[] args) 
    {
        launch();
    }
}
