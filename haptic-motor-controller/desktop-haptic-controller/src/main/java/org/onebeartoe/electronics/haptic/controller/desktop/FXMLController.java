
package org.onebeartoe.electronics.haptic.controller.desktop;

import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.io.IOException;
import java.io.OutputStream;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.stream.Collectors;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;

import org.onebeartoe.electronics.haptic.controller.datasheet.waveform.list.parser.DatasheetWaveformListParser;
import org.onebeartoe.io.serial.SerialPorts;

/**
 * This was tested with the Adafruit EZ Link (adafruit.com/products/1628) using this command:
 * 
 * java -Djava.library.path="c:\opt\rxtx" -jar target/serial-plotter-0.0.1-SNAPSHOT.jar
 * 
 * @author Roberto Marquez
 */
public class FXMLController 
        implements SerialPortEventListener,
                   Initializable
{    
    @FXML
    private Label label;
    
    @FXML
    private ChoiceBox dropdown1;
    
    @FXML
    private ChoiceBox dropdown2;
    
    @FXML
    private ChoiceBox dropdown3;
    
    @FXML
    private ChoiceBox dropdown4;
    
    @FXML
    private ChoiceBox dropdown5;
    
    private List<ChoiceBox> dropdownList;
    
    private SerialPort serialPort;
    
    private Map<Integer, String> hardcodedWaveforms;
    
    Logger logger;
    
    private OutputStream serialOutstream;

    private String buildWaveformList(List<Integer> waveformIds)
    {
        List<String> strs = waveformIds.stream()
                    .map( (i) -> {return String.valueOf(i);} )
                    .collect( Collectors.toList() );
        
        String list = String.join(",", strs);
                
        return list;
    }
    
    private int dropdownIndexToId(ChoiceBox dropdown)
    {
        int i = dropdown.getSelectionModel().getSelectedIndex();
        
        // The ChoiceBox index is zero-based, but the datasheet says the IDs start at 1.
        int id = i + 1;
        
        return id;
    }
    
    private void handleSendOneButtonAction(ChoiceBox dropdown)
    {
        int waveformId = dropdownIndexToId(dropdown);
        
        int id = dropdownIndexToId(dropdown);
        label.setText("Haptic Controller: Waveform " + id);
        
        sendOneWaveformId(waveformId);
    }
    
    @FXML
    private void handleButton1Action(ActionEvent event) 
    {
        handleSendOneButtonAction(dropdown1);
    }
    
    @FXML
    private void handleButton2Action(ActionEvent event)
    {        
        handleSendOneButtonAction(dropdown2);
    }
    
    @FXML
    private void handleButton3Action(ActionEvent event)
    {        
        handleSendOneButtonAction(dropdown3);
    }
    
    @FXML
    private void handleButton4Action(ActionEvent event)
    {        
        handleSendOneButtonAction(dropdown4);
    }
    
    @FXML
    private void handleButton5Action(ActionEvent event)
    {        
        handleSendOneButtonAction(dropdown5);
    }
    
    @FXML
    private void handleSendAllButton(ActionEvent event)
    {
        List<Integer> waveformIds = new ArrayList();
        for(ChoiceBox dropdown : dropdownList)
        {
            int id = dropdownIndexToId(dropdown);                        

            
            if(id > 0)
            {
                String message = String.format("%d ", id);
                logger.info(message);
                
                waveformIds.add(id);
            }
        }
        
        sendWaveformIds(waveformIds);
    }

    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        logger = Logger.getLogger( getClass().getName() );
        
        hardcodedWaveforms = DatasheetWaveformListParser.hardcodedWaveforms();
        
        List<String> effectNames = new ArrayList();

        Set<Integer> keySet = hardcodedWaveforms.keySet();
        
        for(Integer i : keySet)
        {
            String name = hardcodedWaveforms.get(i);
            effectNames.add(name);
        }

        ObservableList<String> ol = FXCollections.observableList(effectNames);
        
        ChangeListener changeListener = new ChangeListener<Number>()
        {
            @Override
            public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue)
            {
                int i = newValue.intValue();
                
                // The ChoiceBox index is zero-based, but the datasheet says the IDs start at 1.
                i += 1;
                
                label.setText("Haptic Controller: Waveform " + i);
                
                sendOneWaveformId(i);
            }
        };
        
        dropdown1.setItems(ol);
        dropdown1.getSelectionModel().selectFirst();        
        dropdown1.getSelectionModel().selectedIndexProperty().addListener(changeListener);
        
        dropdown2.setItems(ol);
        dropdown2.getSelectionModel().selectedIndexProperty().addListener(changeListener);
        
        dropdown3.setItems(ol);
        dropdown3.getSelectionModel().selectedIndexProperty().addListener(changeListener);
        
        dropdown4.setItems(ol);
        dropdown4.getSelectionModel().selectedIndexProperty().addListener(changeListener);
        
        dropdown5.setItems(ol);
        dropdown5.getSelectionModel().selectedIndexProperty().addListener(changeListener);
        
        dropdownList = new ArrayList();
        
        dropdownList.add(dropdown1);
        dropdownList.add(dropdown2);
        dropdownList.add(dropdown3);
        dropdownList.add(dropdown4);
        dropdownList.add(dropdown5);
        
        logger.info("items added");

        // comment this to quickly start the app with no SerialPort features activated.        
        initializeSerialPort();
    }
    
    /**
     * Initialize the serial port.  No serial events are used in this app, 
     * so a call to serialPort.addEventListener() is not needed.
     */
    private void initializeSerialPort()
    {
        try
        {
            serialPort = SerialPorts.get("COM17");
            serialOutstream = serialPort.getOutputStream();
        }
        catch (Exception | NoClassDefFoundError ex)
        {
            String message = "The serial port was not obtained.";
            logger.log(Level.SEVERE, message, ex);
        }
    }
        
    private void sendOneWaveformId(int waveformId)
    {
        List waveformList = new ArrayList();
        waveformList.add(waveformId);
        
        sendWaveformIds(waveformList);
    }
    
    private void sendWaveformIds(List<Integer> waveformIds)
    {
        String waveformList = buildWaveformList(waveformIds);
        
        String consoleMessage = "sending >" + waveformList + "< to serial port";
        logger.log(Level.INFO, consoleMessage);
        
        String message = waveformList + "" + '\n';

        try
        {
            if(serialOutstream == null)
            {
                logger.log(Level.SEVERE, "Not writing to null outstream: serialOutstream");
            }
            else
            {
                serialOutstream.write( message.getBytes() );
            }
        }
        catch (IOException ex)
        {
            message = "could not send >" + waveformList + "< to serial port";
            logger.log(Level.SEVERE, message, ex);
        }
    }
    
    @Override
    public void serialEvent(SerialPortEvent spe)
    {
        String message = "Serial event: " + 
                         spe.getEventType() + ", " + 
                         spe.getNewValue() + ", " + 
                         spe.getOldValue() + ", " + 
                         spe.getSource();
        
        logger.log(Level.INFO, message);
    }
    
    public void shutdown()
    {
        SerialPorts.shutdown(serialPort);
    }    
}