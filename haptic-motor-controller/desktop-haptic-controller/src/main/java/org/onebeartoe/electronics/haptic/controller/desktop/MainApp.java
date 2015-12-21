
package org.onebeartoe.electronics.haptic.controller.desktop;

import java.net.URL;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MainApp extends Application 
{
    private FXMLLoader loader;

    @Override
    public void start(Stage stage) throws Exception 
    {
        URL url = getClass().getResource("/fxml/Scene.fxml");
                
        loader = new FXMLLoader(url);
        
        Parent root = loader.load();
        
        Scene scene = new Scene(root);
        scene.getStylesheets().add("/styles/Styles.css");
        
        stage.setTitle("onebeartoe apps");
        stage.setScene(scene);
        stage.show();
    }

    /**
     * The main() method is ignored in correctly deployed JavaFX application.
     * main() serves only as fallback in case the application can not be
     * launched through deployment artifacts, e.g., in IDEs with limited FX
     * support. NetBeans ignores main().
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        launch(args);
    }
    
    @Override
    public void stop()
    {
        FXMLController controller = loader.getController();
        controller.shutdown();
    }

}
