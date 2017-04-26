/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXCheckBox;
import com.jfoenix.controls.JFXRadioButton;
import java.io.IOException;

import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Orientation;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.text.Text;

/**
 *
 * @author mathieu
 */
public class ControllerTab extends StackPane {

    protected Polygon parallelogram;
    private TabListener listener;
    protected Text tabLabel;
    protected JFXButton closeTab;
    protected boolean plusButton;
    
    public void setTabListener (TabListener listener) {
        this.listener = listener;
    }
   
    public void setColorTabText(boolean active, boolean plusButton){
    	this.plusButton = plusButton;
    	if (active) {
    		tabLabel.setFill(Color.DIMGREY);
    		if(!plusButton) closeTab.setTextFill(Color.DIMGREY);
    		parallelogram.setFill(Color.web("1BEFE9"));
            parallelogram.setStroke(Color.web("00BAB5"));
		} else {
			tabLabel.setFill(Color.web("#FFFFFF"));
			if(!plusButton) closeTab.setTextFill(Color.web("#FFFFFF"));
    		parallelogram.setFill(Color.web("00BAB5"));
    		parallelogram.setStroke(Color.web("00BAB5"));
		}
    }
    
    public void setTabText(String text){
    	if (text.length()>=11) {
    		tabLabel.setText(text.substring(text.length()-7, text.length())+" ");
		} else {
			tabLabel.setText(text);
			for (int i = text.length(); i < 11; i++) {
				tabLabel.setText(tabLabel.getText()+" ");
			}
		}
    }
    
    public ControllerTab(boolean plusButton, final GraphicSearch search) {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLTab.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }

        parallelogram = new Polygon();
        if (plusButton) {
            parallelogram.getPoints().addAll(10.0, 0.0,
                0.0, 38.0,
                50.00, 38.0,
                60.0, 0.0);
        } else {
            parallelogram.getPoints().addAll(10.0, 0.0,
                0.0, 38.0,
                150.00, 38.0,
                160.0, 0.0);
        }
        
        this.getChildren().add(parallelogram);
        
        FlowPane tabControl = new FlowPane(Orientation.VERTICAL);
        tabControl.setAlignment(Pos.CENTER);
        
        if (plusButton) {
            tabLabel = new Text("+");
        } else {
            tabLabel = new Text("New tab" + "    ");
        }
        
        tabControl.getChildren().add(tabLabel);
        
        
        if (!plusButton) {
            closeTab = new JFXButton("X");
            closeTab.setOnMouseClicked(new EventHandler<MouseEvent>() {
				@Override
				public void handle(MouseEvent event) {
				    if (listener != null) listener.onCloseTab(search);
				}
			});
            
            tabControl.getChildren().add(closeTab);
        }
        
        setColorTabText(true, plusButton);
        
        this.getChildren().add(tabControl);
        
        this.setOnMouseClicked(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
			    if (search != null) {
			        search.setActive(true);
			    }
			}
		});
    }

}
