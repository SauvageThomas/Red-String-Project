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
import model.entities.Request;
import model.entities.Result;
import view.GraphicLauncher;

/**
 *
 * @author mathieu
 * 
 * Standard layout for each new tab/window
 */
public class ControllerHomeSearch extends VBox {
	// FXML components
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
    	//Loading and binding corresponding FXML file
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
        
        
        // Adding gray colors to the color picker
        for (int i = 0; i <= 255; i+=5) {
        	colorPicker.getCustomColors().add(Color.grayRgb(i));
		}
        
        //Creating and managing the toggle group for the 3 different searches available
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

        // Binding the radio buttons to their panels
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

        //Binding a file picker to the browse button
        browseButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	File fileChosen = fileChooser.showOpenDialog(browseButton.getScene().getWindow());
            	if (fileChosen != null) browseField.setText(fileChosen.getAbsolutePath());
            }
        });

        // Sending the search request to the controller on launch
        launchButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
            	
            	GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(true);
            	
            	// 3 different methods to call whether the search is by keyword, file or color
                switch (searchGroup.getSelectedToggle().getUserData().toString()) {
                    case "text":
                    	search.searchTab.setTabText(textFieldSearch.getText());
                    	
                    	Request textRequest = controllerSoftware.searchByKeywords(textFieldSearch.getText());
                    	search.currentRequest = textRequest;
                    	
                        search.searchWindow.getChildren().clear();
                        ControllerTextResults textResults = new ControllerTextResults(textRequest.getResults());
                        // Setting the reusult window large enough to take all available space (max 4K, should be enough)
                        textResults.setPrefSize(3840, 2160);
                        search.searchWindow.getChildren().addAll(textResults);
                        break;
                    case "file":
                    	search.searchTab.setTabText(browseField.getText());
                    	
                    	Request fileRequest = controllerSoftware.searchByFile(browseField.getText());
                    	search.currentRequest = fileRequest;
                    	
                        search.searchWindow.getChildren().clear();
                        // Within the first switch, we have to check the type of file given
                        switch (((PathParameter) fileRequest.getSearchParameter()).getType()) {
						case TEXT:
							ControllerTextResults fileTextResults = new ControllerTextResults(fileRequest.getResults());
							fileTextResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(fileTextResults);
							break;
						case IMAGE:
							ControllerImageResults fileImageResults = new ControllerImageResults(fileRequest.getResults(), false);
							fileImageResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(fileImageResults);
	                        break;
						case AUDIO:
							// Since we couldn't use javafx media player, the sound result is displayed as an image result without any pitcure to render
							ControllerImageResults fileAudioResults = new ControllerImageResults(fileRequest.getResults(), true);
							fileAudioResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(fileAudioResults);
							System.out.println(fileRequest.getResults().get(0).getFilePath());
	                        break;
						default:
							// Managing any unknown type (result will say no match for this request)
							ControllerImageResults noResults = new ControllerImageResults(new ArrayList<Result>(), false);
							noResults.setPrefSize(3840, 2160);
	                        search.searchWindow.getChildren().addAll(noResults);
							break;
						}
                        break;
                    case "color":
                    	search.searchTab.setTabText("#".concat(colorPicker.getValue().toString().toUpperCase().substring(2, colorPicker.getValue().toString().length()-2)));
                    	Request colorRequest;
                    	// Casting the given type to an easier one to process
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
                    	ControllerImageResults colorResults = new ControllerImageResults(colorRequest.getResults(), false);
                    	colorResults.setPrefSize(3840, 2160);
                        search.searchWindow.getChildren().addAll(colorResults);
                        break;
                }
            }
        });
    }
}
