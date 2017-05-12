/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.io.File;
import java.io.IOException;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.ScrollPane.ScrollBarPolicy;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import model.entities.History;
import model.entities.Request;
import model.entities.Result;

/**
 *
 * @author mathieu
 * 
 * Controller for a text request
 */
public class ControllerTextResults extends AnchorPane{

    @FXML
    private VBox search;
    
    @FXML
    private ScrollPane scroll;
    
    public ControllerTextResults(History history){
    	//Loading and binding corresponding FXML file
    	FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLTextResults.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        this.scroll.setFitToHeight(true);
        this.scroll.setFitToWidth(true);
        this.scroll.setHbarPolicy(ScrollBarPolicy.NEVER);
        this.scroll.setVbarPolicy(ScrollBarPolicy.AS_NEEDED);
        
        // Creating and adding the results for the request, if request list empty, adding fitting response
        
        if (history.getRequests().size() == 0) {
        	this.search.getChildren().add(new ControllerTextElement("Aucun résultat", "Aucun document ne correspond aux termes de recherche spécifiés", null));
		}
        
        for (Request request : history.getRequests()) {
        	this.search.getChildren().add(new ControllerTextElement("Recherche sauvegardée", request.getSearchParameter().getString(), null));
		}
    }
    
    public ControllerTextResults(List<Result> results) {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(
                "/view/fxml/FXMLTextResults.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        this.scroll.setFitToHeight(true);
        this.scroll.setFitToWidth(true);
        this.scroll.setHbarPolicy(ScrollBarPolicy.NEVER);
        this.scroll.setVbarPolicy(ScrollBarPolicy.AS_NEEDED);
        
        if (results.size() == 0) {
        	this.search.getChildren().add(new ControllerTextElement("Aucun résultat", "Aucun document ne correspond aux termes de recherche spécifiés", null));
		}
        
        for (Result result : results) {
        	File fXmlFile = new File(result.getFilePath());
        	DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        	DocumentBuilder dBuilder;
			try {
				dBuilder = dbFactory.newDocumentBuilder();
				Document doc = dBuilder.parse(fXmlFile);
				this.search.getChildren().add(new ControllerTextElement(doc.getElementsByTagName("titre").item(0).getTextContent(), doc.getElementsByTagName("resume").item(0).getTextContent(), result.getFilePath()));
			} catch (ParserConfigurationException e) {
				System.out.println("ERROR PASING XML");
			} catch (SAXException e) {
				System.out.println("ERROR PASING XML");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }
    }
    
}
