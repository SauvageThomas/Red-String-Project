package view.controller;

import java.io.IOException;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXProgressBar;

import controller.ControllerSoftware;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class ControllerUpdateBD extends AnchorPane{
	@FXML
    private JFXButton updateButton;
	@FXML
    private JFXButton cancelButton;
	@FXML
    private Text titleText;
	@FXML
    private Text progressText;
	@FXML
    private JFXProgressBar progressBar;
	
	public ControllerUpdateBD(final ControllerSoftware controllerSoftware, final Stage stage){
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLUpdateDB.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
		
		progressBar.setStyle("-fx-progress-color: #00BAB5");
		titleText.setText("Update Database");
		titleText.setFont(Font.font ("Helvetica", 20));
		titleText.setFill(Color.web("#00BAB5"));
		
		progressText.setText("");
		progressText.setFont(Font.font ("Helvetica", 15));
		progressText.setFill(Color.web("#00BAB5"));
		
		updateButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	progressBar.setProgress(0.05);
            	progressText.setText("Indexing text files");
            	controllerSoftware.indexText();
            	progressBar.setProgress(0.55);
            	progressText.setText("Indexing image files");
            	controllerSoftware.indexImage();
            	progressBar.setProgress(0.70);
            	progressText.setText("Indexing sound files");
            	controllerSoftware.indexSound();
            	progressBar.setProgress(1.0);
            	stage.close();
            }
        });
		
		cancelButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	stage.close();
            }
        });
	}
}
