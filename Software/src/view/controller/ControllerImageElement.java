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
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import view.GraphicLauncher;

/**
 *
 * @author mathieu
 */
public class ControllerImageElement extends AnchorPane{
    
    @FXML
    private HBox imageElement;

    public ControllerImageElement(final String url, boolean audioTest) {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLImageElement.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        System.out.println(url);
        ImageView test = new ImageView("file:"+url);
        String[] nameImage = url.split("/");
        test.setFitHeight(200);
        test.setPreserveRatio(true);
        test.setSmooth(true);
        test.setCache(true);
        
        //MediaView test2 = new MediaView(new MediaPlayer(new Media("file:../data/epic.wav")));
        
        imageElement.getChildren().add(test);
        
        VBox imageInfos = new VBox();
        Text titleDisplay = new Text(nameImage[nameImage.length-1]);
        titleDisplay.setFont(Font.font ("Helvetica", 40));
        titleDisplay.setFill(Color.web("#00BAB5"));
        imageInfos.getChildren().add(titleDisplay);
        
        if (!audioTest) {
        	Text contentDisplay = new Text("Taille de l'image : " + (int) test.getImage().getWidth() + "x" + (int) test.getImage().getHeight());
            contentDisplay.setFont(Font.font ("Helvetica", 20));
            contentDisplay.setFill(Color.DARKGRAY);
            imageInfos.getChildren().add(contentDisplay);
		}
        
        imageInfos.setPadding(new Insets(0,0,0,10));
        imageElement.getChildren().add(imageInfos);
        
        imageElement.setPadding(new Insets(5,0,5,5));
        this.setEffect(new DropShadow(5,3,3, Color.LIGHTGRAY));
        
        imageElement.setOnMouseClicked(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
			    try {
					Runtime.getRuntime().exec("xdg-open "+url);
				} catch (IOException e) {}
			}
		});
        
        imageElement.setOnMouseEntered(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
				if (url != null) {
		        	GraphicLauncher.getInstance().getScene().setCursor(Cursor.HAND);
				}
			}
		});
        
        imageElement.setOnMouseExited(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
				if (url != null) {
		        	GraphicLauncher.getInstance().getScene().setCursor(Cursor.DEFAULT);
				}
			}
		});
    }
    
}
