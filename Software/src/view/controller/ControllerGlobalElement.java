package view.controller;

import java.io.File;
import java.io.IOException;
import java.util.Map;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXTextField;
import com.jfoenix.controls.JFXToggleButton;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import javafx.stage.DirectoryChooser;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import model.entities.Setting;

public class ControllerGlobalElement extends AnchorPane{
	@FXML
	protected JFXTextField bdPath;
	@FXML
	protected JFXButton bdButton;
	@FXML
	protected JFXToggleButton openMode;
	@FXML
	protected JFXButton save;
	
	public ControllerGlobalElement(final Stage stage, final Map<String, Setting> settings, String name){
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLSettingGlobal.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        bdPath.setStyle("-jfx-focus-color: #00BAB5");
        
        bdPath.setText(settings.get("DATA BASE").getValue());
        boolean select;
        if (settings.get("MODE").getValue().equals("open")) select = true;
		else select = false;
        openMode.setSelected(select);
        
        save.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	settings.get("DATA BASE").setValue(bdPath.getText());
            	if (openMode.isSelected()) settings.get("MODE").setValue("open");	
				else settings.get("MODE").setValue("close");	
            	//controllerSoftware.submitSettings(name);
            	stage.close();
            }
        });
        
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
