package view.controller;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXProgressBar;

import controller.ControllerSoftware;
import javafx.event.Event;
import javafx.scene.Cursor;
import javafx.scene.Scene;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class IndexThread extends Thread{
	
	private ControllerSoftware controllerSoftware;
	
	private Stage stage;
	private JFXProgressBar progressBar;
	private Text progressText;
	private JFXButton doneButton;
	
	public IndexThread(ControllerSoftware controllerSoftware, JFXProgressBar progressBar, Text progressText, JFXButton doneButton, Stage stage){
		this.controllerSoftware = controllerSoftware;
		this.stage = stage;
		this.progressBar = progressBar;
		this.progressText = progressText;
		this.doneButton = doneButton;
	}
	
	@Override
	public synchronized void run() {
		try {
			stage.getScene().setCursor(Cursor.WAIT);
			controllerSoftware.indexText();
			progressBar.setProgress(0.55);
        	progressText.setText("Indexing image files");
        	controllerSoftware.indexImage();
        	progressBar.setProgress(0.70);
        	progressText.setText("Indexing sound files");
        	controllerSoftware.indexSound();
        	progressBar.setProgress(1.0);
        	progressText.setText("Database successfully indexed");
        	stage.getScene().setCursor(Cursor.DEFAULT);
        	doneButton.setVisible(true);
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
}
