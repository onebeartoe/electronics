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
    
    private LedNumber temperatureTensLed;
    private LedNumber temperatureOnesLed;
    private LedNumber temperatureTenthsLed;
    
    private LedNumber humidityTensLed;
    private LedNumber humidityOnesLed;
    private LedNumber humidityTenthsLed;
    
    private SerialPort serialPort;
    
    private boolean convertToFahrenheit = false;
    
    private Label tempUnitLabel;
    
    @Override
    public void init()
    {
        temperatureTensLed = initializeLedNumber();
        temperatureOnesLed = initializeLedNumber(true);
        temperatureTenthsLed = initializeLedNumber();
        
        humidityTensLed = initializeLedNumber();
        humidityOnesLed = initializeLedNumber(true);
        humidityTenthsLed = initializeLedNumber();
        
        tempUnitLabel = initializeLabel("c");
        tempUnitLabel.setOnMouseClicked((event) -> 
        {
            if(convertToFahrenheit)
            {
                tempUnitLabel.setText("c");
            }
            else
            {
                tempUnitLabel.setText("f");
            }

            convertToFahrenheit = !convertToFahrenheit;
        });
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
        
        HBox temperatureHBox = new HBox();
        temperatureHBox.setSpacing(10);
        temperatureHBox.setAlignment(Pos.CENTER);        
        temperatureHBox.getChildren().addAll(temperatureLabel, 
                temperatureTensLed,
                    temperatureOnesLed,
                    temperatureTenthsLed,
                    tempUnitLabel);

        var humidityLabel = initializeLabel("      Humidity");
        var percentLabel = initializeLabel("%");
        HBox humidityHBox = new HBox();
        humidityHBox.setSpacing(10);
        humidityHBox.setAlignment(Pos.CENTER);        
        humidityHBox.getChildren().addAll(humidityLabel,
                                    humidityTensLed,
                                    humidityOnesLed,
                                    humidityTenthsLed,
                                    percentLabel);
        
        var separator = new Separator();        
        var style = "-fx-border-color:#FFFFFF; -fx-border-width:2";        
        separator.setStyle(style);

        var mainVbox = new VBox();
        mainVbox.setSpacing(25);
        mainVbox.setPadding(new Insets(10));
        mainVbox.setStyle("-fx-background-color: black;");
        mainVbox.getChildren().addAll(temperatureHBox,
                                    separator,
                                    humidityHBox);
        
        var scene = new Scene(mainVbox, 640, 300);
        
        stage.setScene(scene);
        stage.show();

        // the SHT41 Trinkey appears as this port name        
        var portName = "/dev/ttyACM0";
//        serialPort = SerialPort.getCommPort(portName);
        serialPort = SerialPort.getCommPorts()[0];
        serialPort.openPort();
        serialPort.addDataListener(this);
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

        var instream = serialPort.getInputStream();

        try 
        {
            var buffStream = new BufferedReader(new InputStreamReader(instream));            

            String line = buffStream.readLine();

            System.out.println("one = " + line);
            
            SensorReading reading = parseLine(line);
            
            if(reading instanceof TemperatureReading tempReading)
            {
                updateTemperatureLeds(tempReading);
            }
            else if(reading instanceof HumidityReading humidityReading)
            {
                updateHumidityLed(humidityReading);
            }
            else
            {
// TODO: maybe change the LEDs to show an error???
                var message = String.format("There was an error with >%s<", line);
                System.err.println(message);
            }
        } 
        catch (IOException  ex) 
        {
            var message = ex.getMessage();

            logger.log(Level.SEVERE, message, ex);
        }
    }    

    @Override
    public void stop()
    {
        System.out.println("buh buy");
        serialPort.closePort();
        // Save file
    }    
    
    private Label initializeLabel(String text)
    {                
        var fontSize = 56.0f;        
        var labelFont = new Font(fontSize);      
        
        var label = new Label(text);
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
        return new LedNumber(DisplaySkin.CLASSIC, 
                          Color.BLACK, 
                               Color.BLACK, 
                            Color.RED, 
                                       showDot);
    }    
    
    public static void main(String[] args) 
    {
        launch();
    }

//TODO: remove this method and inline the call to SensorReadings#parseLine
    private SensorReading parseLine(String line) 
    {
        SensorReading reading = SensorReadings.parseLine(line);
        
        return reading;        
    }

    private void updateTemperatureLeds(TemperatureReading reading) 
    {
        var value = reading.temperature();
        
        if(convertToFahrenheit)
        {
            // T(oF) = (T(oC) × (9/5)) + 32
            value = (value * (9.0f/5.0f)) + 32;
        }
        
        int intCast = (int) value;
        
        int tensDigit = Integer.MIN_VALUE;

        if(value < 10)
        {
            temperatureTensLed.highlight(HighlightType.CLEAR.CLEAR);
        }
        else
        {            
            tensDigit = intCast / 10;

            var highlights = HighlightType.getByNumber(tensDigit);

            temperatureTensLed.highlight(highlights);
            
        }
        
        int onesValue = intCast % 10;
        var onesHightLights = HighlightType.getByNumber(onesValue);
        temperatureOnesLed.highlight(onesHightLights, true);
        
        float floatingPart = value - (int) value;
System.out.println("floatingPart = " + floatingPart);        
        int tenths = (int) (floatingPart * 10);
System.out.println("tenths = " + tenths);        
        var tenthsHighLights = HighlightType.getByNumber(tenths);
        temperatureTenthsLed.highlight(tenthsHighLights);
        
        String tempOut = String.format("reading to temperature LEDs: %d-%d-%d", tensDigit, onesValue, tenths);
        System.out.println(tempOut);
    }

    private void updateHumidityLed(HumidityReading reading) {
        var value = reading.humidity();
        
        int intCast = (int) value;
        
        int tensDigit = Integer.MIN_VALUE;

        if(value < 10)
        {
            humidityTensLed.highlight(HighlightType.CLEAR.CLEAR);
        }
        else
        {            
            tensDigit = intCast / 10;

            var highlights = HighlightType.getByNumber(tensDigit);

            humidityTensLed.highlight(highlights);
            
        }
        
        int onesValue = intCast % 10;
        var onesHightLights = HighlightType.getByNumber(onesValue);
        humidityOnesLed.highlight(onesHightLights, true);
        
        float floatingPart = value - (int) value;
System.out.println("floatingPart = " + floatingPart);        
        int tenths = (int) (floatingPart * 10);
System.out.println("tenths = " + tenths);        
        var tenthsHighLights = HighlightType.getByNumber(tenths);
        humidityTenthsLed.highlight(tenthsHighLights);
        
        String humidityOut = String.format("reading to humidity LEDs: %d-%d-%d", tensDigit, onesValue, tenths);
        System.out.println(humidityOut);
    }
}
