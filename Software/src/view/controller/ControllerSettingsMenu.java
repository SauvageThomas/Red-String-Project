package view.controller;

import java.io.IOException;

import com.jfoenix.controls.JFXButton;

import controller.ControllerSoftware;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import model.entities.Settings;

/**
*
* @author mathieu
* 
* Controller for the general window of settings
*/
public class ControllerSettingsMenu extends HBox{
	//FXML components
	@FXML
	protected VBox settingsList;
	
	@FXML
	protected StackPane currentWindow;
	
	public ControllerSettingsMenu(final ControllerSoftware controllerSoftware, final Stage stage){
		
		Settings globalSetting = null;
		//Loading and binding corresponding FXML file
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLSettingsMenu.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
		
        stage.setResizable(false);
        
		for (final Settings settings : controllerSoftware.getAllSettings()) {
			JFXButton button = new JFXButton(settings.getName());
			button.setStyle("-fx-background-color: #FFFFFF");
			button.setPrefSize(120, 60);
			settingsList.getChildren().add(button);
			//Depending on the name of the button, creating specific window of settings
			if (!settings.getName().equals("Global")) {
				button.setOnAction(new EventHandler<ActionEvent>() {
	                @Override
	                public void handle(ActionEvent e) {
	                	currentWindow.getChildren().clear();
	                	currentWindow.getChildren().add(new ControllerSettingElement(stage, settings.getSettings(), settings.getName(), controllerSoftware));
	                }
	            });
			} else {
				globalSetting = settings;
				button.setOnAction(new EventHandler<ActionEvent>() {
	                @Override
	                public void handle(ActionEvent e) {
	                	currentWindow.getChildren().clear();
	                	currentWindow.getChildren().add(new ControllerGlobalElement(stage, settings.getSettings(), settings.getName(), controllerSoftware));
	                }
	            });
			}
		}
		// Clearing the window then adding requested layout
		currentWindow.getChildren().clear();
		currentWindow.getChildren().add(new ControllerGlobalElement(stage, globalSetting.getSettings(), globalSetting.getName(), controllerSoftware));
	}
}
