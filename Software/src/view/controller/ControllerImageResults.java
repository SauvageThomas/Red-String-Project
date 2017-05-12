/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.io.IOException;
import java.util.List;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import model.entities.Result;

/**
 *
 * @author mathieu
 * 
 * Controller for a picture request
 */
public class ControllerImageResults extends AnchorPane{
    // FXML components
    @FXML
    private ScrollPane scroll;
    
    @FXML
    private VBox search;

    public ControllerImageResults(List<Result> results, boolean audioTest) {
    	//Loading and binding corresponding FXML file
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLImageResults.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        this.scroll.setFitToHeight(true);
        this.scroll.setFitToWidth(true);
        this.scroll.setHbarPolicy(ScrollPane.ScrollBarPolicy.NEVER);
        this.scroll.setVbarPolicy(ScrollPane.ScrollBarPolicy.AS_NEEDED);
        
        // Creating and adding the results for the request, if request list empty, adding fitting response
        
        if (results.size() == 0) {
        	this.search.getChildren().add(new ControllerTextElement("Aucun résultat", "Aucun document ne correspond aux termes de recherche spécifiés", null));
		}
        
        for (Result result : results) {
            search.getChildren().add(new ControllerImageElement(result.getFilePath(), audioTest));
        }
    }
}
