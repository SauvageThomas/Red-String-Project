/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXColorPicker;
import com.jfoenix.controls.JFXRadioButton;

import controller.ControllerSoftware;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.control.TextField;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.FileChooser;
import model.entities.PathParameter;
import model.entities.history.Request;
import model.entities.history.Result;

/**
 *
 * @author mathieu
 */
public class ControllerHomeSearch extends VBox {

    @FXML
    private JFXRadioButton textSearch;

    @FXML
    private JFXRadioButton fileSearch;

    @FXML
    private JFXRadioButton colorSearch;

    @FXML
    private TextField textFieldSearch;

    @FXML
    private JFXColorPicker colorPicker;

    @FXML
    private JFXButton browseButton;
    
    @FXML
    private TextField browseField;
    
    @FXML
    private HBox browse;

    @FXML
    private JFXButton launchButton;

    public ControllerHomeSearch(final GraphicSearch search, final ControllerSoftware controllerSoftware) {
    	
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLHomeSearch.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        final FileChooser fileChooser = new FileChooser();

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        for (int i = 0; i <= 255; i+=5) {
        	colorPicker.getCustomColors().add(Color.grayRgb(i));
		}
        
        textFieldSearch.setVisible(true);
        colorPicker.setVisible(false);
        browse.setVisible(false);

        textSearch.setSelected(true);
        
        browse.setMargin(browseButton, new Insets(0,0,0,5));

        final ToggleGroup searchGroup = new ToggleGroup();
        textSearch.setUserData("text");
        textSearch.setToggleGroup(searchGroup);
        fileSearch.setUserData("file");
        fileSearch.setToggleGroup(searchGroup);
        colorSearch.setUserData("color");
        colorSearch.setToggleGroup(searchGroup);

        searchGroup.selectedToggleProperty().addListener(
                new ChangeListener<Toggle>() {
            @Override
            public void changed(ObservableValue<? extends Toggle> ov, Toggle old_toggle, Toggle new_toggle) {
                if (searchGroup.getSelectedToggle() != null) {
                    switch (searchGroup.getSelectedToggle().getUserData().toString()) {
                        case "text":
                            textFieldSearch.setVisible(true);
                            colorPicker.setVisible(false);
                            browse.setVisible(false);
                            break;
                        case "file":
                            textFieldSearch.setVisible(false);
                            colorPicker.setVisible(false);
                            browse.setVisible(true);
                            break;
                        case "color":
                            colorPicker.setVisible(true);
                            textFieldSearch.setVisible(false);
                            browse.setVisible(false);
                            break;
                    }
                }
            }
        });

        browseButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	File fileChosen = fileChooser.showOpenDialog(browseButton.getScene().getWindow());
            	if (fileChosen != null) browseField.setText(fileChosen.getAbsolutePath());
            }
        });

        launchButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                switch (searchGroup.getSelectedToggle().getUserData().toString()) {
                    case "text":
                    	search.searchTab.setTabText(textFieldSearch.getText());
                    	
                    	Request textRequest = controllerSoftware.searchByKeywords(textFieldSearch.getText());
                    	search.currentRequest = textRequest;
                    	
                        search.searchWindow.getChildren().clear();
                        ControllerTextResults textResults = new ControllerTextResults(textRequest.getResults());
                        textResults.setPrefSize(3840, 2160);
                        search.searchWindow.getChildren().addAll(textResults);
                        break;
                    case "file":
                    	search.searchTab.setTabText(browseField.getText());
                    	
                    	Request fileRequest = controllerSoftware.searchByFile(browseField.getText());
                    	search.currentRequest = fileRequest;
                    	
                        search.searchWindow.getChildren().clear();
                        switch (((PathParameter) fileRequest.getSearchParameter()).getType()) {
						case TEXT:
							ControllerTextResults fileTextResults = new ControllerTextResults(fileRequest.getResults());
							fileTextResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(fileTextResults);
							break;
						case IMAGE:
							ControllerImageResults fileImageResults = new ControllerImageResults(fileRequest.getResults());
							fileImageResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(fileImageResults);
	                        break;
						case AUDIO:
							/*ControllerAudioResults fileAudioResults = new ControllerAudioResults(fileRequest.getResults());
							fileAudioResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(fileAudioResults);*/
	                        break;
						default:
							ControllerImageResults noResults = new ControllerImageResults(new ArrayList<Result>());
							noResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(noResults);
							break;
						}
                        break;
                    case "color":
                    	search.searchTab.setTabText("#".concat(colorPicker.getValue().toString().toUpperCase().substring(2, colorPicker.getValue().toString().length()-2)));
                    	Request colorRequest;
                    	int redValue = (int) (colorPicker.getValue().getRed()*255);
                    	int greenValue = (int) (colorPicker.getValue().getGreen()*255);
                    	int blueValue = (int) (colorPicker.getValue().getBlue()*255);
                    	if (redValue == greenValue && greenValue == blueValue) {
                    		colorRequest = controllerSoftware.searchByShadeOfGray(redValue);
						} else {
							colorRequest = controllerSoftware.searchByColor(redValue, greenValue, blueValue);
						}
                    	search.currentRequest = colorRequest;
                    	
                    	search.searchWindow.getChildren().clear();
                    	ControllerImageResults colorResults = new ControllerImageResults(colorRequest.getResults());
                    	colorResults.setPrefSize(3840, 2160);
                        search.searchWindow.getChildren().addAll(colorResults);
                        break;
                }
            }
        });
    }
}
