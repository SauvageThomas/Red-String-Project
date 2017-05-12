package view.controller;

import java.io.File;
import java.io.IOException;
import java.util.Map;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXSlider;
import com.jfoenix.controls.JFXTextField;

import controller.ControllerSoftware;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;
import model.entities.Setting;


/**
*
* @author mathieu
* 
* Controller for the QTIL page of settings
*/
public class ControllerSettingElement extends AnchorPane{
	//FXML components
	@FXML
	protected JFXSlider pixelSlider;
	@FXML
	protected JFXSlider audioSlider;
	@FXML
	protected JFXSlider audioSlider2;
	@FXML
	protected JFXSlider pixelMarginSlider;
	@FXML
	protected JFXButton save;

	public ControllerSettingElement(final Stage stage, final Map<String, Setting> settings, final String name, final ControllerSoftware controllerSoftware){
		//Loading and binding corresponding FXML file
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
				"/view/fxml/FXMLSettingElement.fxml"));
		fxmlLoader.setRoot(this);
		fxmlLoader.setController(this);

		try {
			fxmlLoader.load();
		} catch (IOException exception) {
			throw new RuntimeException(exception);
		}

		// Setting min, max and current value of every slider
		pixelSlider.setMin(2);
		pixelSlider.setMax(16);
		pixelSlider.setValue(Integer.valueOf(settings.get("QUANTIFICATION").getValue()));

		audioSlider.setMin(50);
		audioSlider.setMax(500);
		audioSlider.setValue(Integer.valueOf(settings.get("LAYER NUMBER").getValue()));

		audioSlider2.setMin(50);
		audioSlider2.setMax(1000);
		audioSlider2.setValue(Integer.valueOf(settings.get("WINDOW SIZE").getValue()));

		pixelMarginSlider.setMin(10);
		pixelMarginSlider.setMax(120);
		pixelMarginSlider.setValue(Integer.valueOf(settings.get("PIXEL MARGIN").getValue()));

		
		// Getting and passing new values on saving
		save.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				try {
					controllerSoftware.changeSetting("LAYER NUMBER", String.valueOf(Math.round(audioSlider.getValue())));
					controllerSoftware.changeSetting("QUANTIFICATION", String.valueOf(Math.round(pixelSlider.getValue())));
					controllerSoftware.changeSetting("WINDOW SIZE", String.valueOf(Math.round(audioSlider2.getValue())));
					controllerSoftware.changeSetting("PIXEL MARGIN", String.valueOf(Math.round(pixelMarginSlider.getValue())));
					controllerSoftware.submitSettings(name);
				} catch (IOException e1) {
					System.out.println("ERROR SUBMIT SETTINGS");
					e1.printStackTrace();
				}
				stage.close();
			}
		});
	}
}
