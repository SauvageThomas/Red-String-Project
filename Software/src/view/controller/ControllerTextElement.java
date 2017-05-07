/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.io.IOException;

import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Cursor;
import javafx.scene.effect.DropShadow;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import model.entities.history.Request;

/**
 *
 * @author mathieu
 */
public class ControllerTextElement extends AnchorPane implements ResizeListener{
    
    @FXML
    private VBox textElement;
    
    private Text titleDisplay;
    
    private Text contentDisplay;

    public ControllerTextElement(String title, String content, final String path) {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLTextElement.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        GraphicLauncher.getInstance().setResizeListener(this);
        
        titleDisplay = new Text(title);
        titleDisplay.setFont(Font.font ("Helvetica", 20));
        titleDisplay.setFill(Color.web("#00BAB5"));
        titleDisplay.setWrappingWidth(700-30);
        textElement.getChildren().add(titleDisplay);
        
        contentDisplay = new Text(content);
        contentDisplay.setFont(Font.font ("Helvetica", 11));
        contentDisplay.setFill(Color.DARKGRAY);
        contentDisplay.setWrappingWidth(700-30);
        textElement.getChildren().add(contentDisplay);
        
        textElement.setPadding(new Insets(2,0,0,5));
        this.setEffect(new DropShadow(5,3,3, Color.LIGHTGRAY));
        
        textElement.setOnMouseClicked(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
			    try {
			    	if (path != null) {
			    		Runtime.getRuntime().exec("xdg-open "+path);
					}
				} catch (IOException e) {}
			}
		});
        
        textElement.setOnMouseEntered(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
				if (path != null) {
		        	GraphicLauncher.getInstance().getScene().setCursor(Cursor.HAND);
				}
			}
		});
        
        textElement.setOnMouseExited(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
				if (path != null) {
		        	GraphicLauncher.getInstance().getScene().setCursor(Cursor.DEFAULT);
				}
			}
		});
    }

	@Override
	public void onResize() {
		titleDisplay.setWrappingWidth(textElement.getWidth()-5);
		contentDisplay.setWrappingWidth(textElement.getWidth()-5);
	}
    
}
