package view.controller;

import java.io.IOException;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXTextField;

import controller.ControllerSoftware;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

public class ControllerLogin extends AnchorPane{
	
	@FXML
	private JFXTextField passwdField;
	
	@FXML
	private JFXButton submit;
	
	public ControllerLogin(final ControllerSoftware controller, final Stage stage, final ControllerSideMenu controllerSideManu){
		
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLLoginMenu.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
		
        passwdField.setStyle("-jfx-focus-color: #00BAB5");
        
		submit.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	if (controller.loginAsAdmin(passwdField.getText())) {
					stage.close();
					controllerSideManu.login.setText("Connecté");
					controllerSideManu.login.setDisable(true);
				} else {
					passwdField.clear();
					passwdField.setPromptText("Wrong password");
					passwdField.setStyle("-jfx-focus-color: #FF0000");
				}
            }
        });
	}
}
