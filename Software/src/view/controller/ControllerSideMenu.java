package view.controller;

import java.io.IOException;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXDrawer;

import controller.ControllerSoftware;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import model.entities.History;
import model.entities.Request;


/**
*
* @author mathieu
* 
* Controller for the side menu
*/
public class ControllerSideMenu extends VBox{
	// FXML components
	@FXML
	protected JFXButton settings;
	
	@FXML
	protected JFXButton login;
	
	@FXML
	protected JFXButton history;
	
	public ControllerSideMenu(final ControllerSoftware controllerSoftware, final GraphicSearchGroup group, final ControllerBase controllerBase, final JFXDrawer drawer){
		//Loading and binding corresponding FXML file
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLSideMenu.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
		
        final ControllerSideMenu memory = this;
        
        
        // Binding all of the buttons to their corresponding windows and disabling settings until admin logged in
        settings.setDisable(true);
        
        settings.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	Stage stage = new Stage();
				ControllerSettingsMenu controllerSettings = new ControllerSettingsMenu(controllerSoftware, stage);
				stage.setTitle("Préférences");
				Scene newScene = new Scene((Parent) controllerSettings);
				stage.setScene(newScene);
				stage.show();
            }
        });
        
		login.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	Stage stage = new Stage();
				ControllerLogin controllerLogin = new ControllerLogin(controllerSoftware, stage, memory);
				stage.setTitle("Connexion");
				Scene newScene = new Scene((Parent) controllerLogin);
				stage.setScene(newScene);
				stage.show();
            }
        });
		
		history.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	GraphicSearch newSearch = new GraphicSearch(group, controllerSoftware);
			    newSearch.searchTab.setTabListener(controllerBase);
			    group.addSearch(newSearch);
			    
			    Request textRequest = controllerSoftware.searchByKeywords("");
			    newSearch.currentRequest = textRequest;
			    
			    newSearch.searchWindow.getChildren().clear();
                ControllerTextResults textResults = new ControllerTextResults(History.getInstance());
                textResults.setPrefSize(3840, 2160);
                newSearch.searchTab.setTabText("History");
                newSearch.searchWindow.getChildren().addAll(textResults);
                drawer.close();
            }
        });
	}
}
