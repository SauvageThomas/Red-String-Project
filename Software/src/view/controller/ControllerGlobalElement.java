package view.controller;

import java.io.File;
import java.io.IOException;
import java.util.Map;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXTextField;
import com.jfoenix.controls.JFXToggleButton;

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
* Graphic controller for the general settings of the app
*/
public class ControllerGlobalElement extends AnchorPane{
	// FXML components
	@FXML
	protected JFXTextField bdPath;
	@FXML
	protected JFXButton bdButton;
	@FXML
	protected JFXToggleButton openMode;
	@FXML
	protected JFXButton save;

	public ControllerGlobalElement(final Stage stage, final Map<String, Setting> settings, final String name, final ControllerSoftware controllerSoftware){
		//Loading and binding corresponding FXML file
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
				"/view/fxml/FXMLSettingGlobal.fxml"));
		fxmlLoader.setRoot(this);
		fxmlLoader.setController(this);

		try {
			fxmlLoader.load();
		} catch (IOException exception) {
			throw new RuntimeException(exception);
		}

		
		// Setting color and values for graphic components
		bdPath.setStyle("-jfx-focus-color: #00BAB5");

		bdPath.setText(settings.get("DATA BASE").getValue());
		boolean select;
		if (settings.get("MODE").getValue().equals("open")) 
			select = true;
		else 
			select = false;
		openMode.setSelected(select);

		// Sending informations from the components to the software controller on saving
		save.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				String mode;
				if (openMode.isSelected()) 
					mode = "open";	
				else 
					mode = "close";

				try {
					controllerSoftware.changeSetting("MODE", mode);
					controllerSoftware.changeSetting("DATA BASE", bdPath.getText() + "/");
					controllerSoftware.submitSettings(name);
				} catch (IOException e1) {
					System.out.println("ERROR SUBMIT SETTINGS");
					e1.printStackTrace();
				}
				stage.close();
			}
		});

		
		// Binding a directory chooser to the Browse button
		final DirectoryChooser directoryChooser = new DirectoryChooser();

		bdButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				File directoryChosen = directoryChooser.showDialog(bdButton.getScene().getWindow());
				if (directoryChosen != null) bdPath.setText(directoryChosen.getAbsolutePath());
			}
		});
	}
}
