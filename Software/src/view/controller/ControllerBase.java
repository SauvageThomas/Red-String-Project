/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXColorPicker;
import com.jfoenix.controls.JFXDrawer;
import com.jfoenix.controls.JFXHamburger;
import com.jfoenix.controls.JFXRadioButton;
import com.jfoenix.controls.JFXTabPane;
import com.jfoenix.controls.events.JFXDrawerEvent;
import com.jfoenix.transitions.hamburger.HamburgerBasicCloseTransition;
import com.jfoenix.transitions.hamburger.HamburgerSlideCloseTransition;

import controller.ControllerHistory;
import controller.ControllerSoftware;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.TranslateTransition;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.control.TextField;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 *
 * @author mathieu
 */
public class ControllerBase implements Initializable, TabListener {

    @FXML
    private JFXHamburger ham;

    @FXML
    private JFXDrawer drawer;

    @FXML
    private StackPane currentWindow;

    @FXML
    private HBox header;
    
    @FXML
    private JFXButton homeButton;
    
    @FXML
    private JFXButton saveButton;

    private GraphicSearchGroup group;
    
    private ControllerSoftware controllerSoftware;
    
    private ControllerHistory controllerHistory;

    @Override
    public void initialize(URL url, ResourceBundle rb) {

        try {

        	controllerSoftware = new ControllerSoftware();
        	controllerHistory = new ControllerHistory();
        	
            group = new GraphicSearchGroup();
            group.setTabListener(this);

            final HamburgerBasicCloseTransition burgerTask = new HamburgerBasicCloseTransition(ham);
            burgerTask.setRate(-1);

            drawer.setSidePane(new ControllerSideMenu(controllerSoftware, group, ControllerBase.this, drawer));

            /*TranslateTransition tt = new TranslateTransition(Duration.millis(2000), text);
            tt.setByX(200f);
            tt.setCycleCount(1);
            tt.setAutoReverse(true);*/
            ham.addEventHandler(MouseEvent.MOUSE_PRESSED, new EventHandler<MouseEvent>() {
                @Override
                public void handle(MouseEvent e) {
                    ham.requestFocus();
                    //burgerTask.setRate(burgerTask.getRate()*-1);
                    if (drawer.isShown()) {
                        drawer.close();
                    } else {
                        drawer.open();
                    }
                    //burgerTask.play();

                    /*tt.play();
				    tt.setByX(tt.getByX()*-1);*/
                }
            });

            drawer.setOnDrawerClosing(new EventHandler<JFXDrawerEvent>() {
                @Override
                public void handle(JFXDrawerEvent e) {
                    burgerTask.setRate(-1);
                    currentWindow.toFront();
                    burgerTask.play();
                }
            });

            drawer.setOnDrawerOpening(new EventHandler<JFXDrawerEvent>() {
                @Override
                public void handle(JFXDrawerEvent e) {
                    burgerTask.setRate(1);
                    currentWindow.toBack();
                    burgerTask.play();
                }
            });

            ControllerTab newTabButton = new ControllerTab(true, null);
            header.getChildren().add(newTabButton);
            //header.setMargin(ham, new Insets(0, -50, 0, 0));
            header.setMargin(newTabButton, new Insets(0, 40, 0, 0));

            newTabButton.setOnMouseClicked(new EventHandler<MouseEvent>() {
				@Override
				public void handle(MouseEvent event) {
				    GraphicSearch newSearch = new GraphicSearch(group, controllerSoftware);
				    newSearch.searchTab.setTabListener(ControllerBase.this);
				    group.addSearch(newSearch);
				}
			});
            
            Event.fireEvent(newTabButton, new MouseEvent(MouseEvent.MOUSE_CLICKED, 0,
                    0, 0, 0, MouseButton.PRIMARY, 1, true, true, true, true,
                    true, true, true, true, true, true, null));
            
            homeButton.setOnAction(new EventHandler<ActionEvent>() {
                @Override
                public void handle(ActionEvent e) {
                	for (GraphicSearch search : group.searchList) {
						if (search.active && search.currentRequest != null) {
							search.currentRequest = null;
							search.searchWindow.getChildren().clear();
							search.searchWindow.getChildren().add(new ControllerHomeSearch(search, controllerSoftware));
							search.searchTab.setTabText("New Tab");
						}
					}
                }
            });
            
            saveButton.setOnAction(new EventHandler<ActionEvent>() {
                @Override
                public void handle(ActionEvent e) {
                	for (GraphicSearch search : group.searchList) {
						if (search.active && search.currentRequest != null && search.currentRequest.getResults().size() != 0) {
							controllerHistory.saveRequest(search.currentRequest);
						}
					}
                }
            });

            //ControllerHomeSearch newSearch = new ControllerHomeSearch();
            /*ArrayList<String> test = new ArrayList<>();
            test.add("test1");
            test.add("test2");
            ControllerTextSearch newSearch = new ControllerTextSearch(test);*/
            //currentWindow.getChildren().add(newSearch);
        } catch (IOException ex) {
            Logger.getLogger(ControllerBase.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    @Override
    public void onNewTab(GraphicSearch newSearch) {
        header.getChildren().add(newSearch.searchTab);
        header.setMargin(newSearch.searchTab, new Insets(0, 90, 0, 0));
        currentWindow.getChildren().add(newSearch.searchWindow);
    }

    @Override
    public void onCloseTab(GraphicSearch removedSearch) {
        header.getChildren().remove(removedSearch.searchTab);
        currentWindow.getChildren().remove(removedSearch.searchWindow);
        group.getSearchList().remove(removedSearch);
        if ((!group.getSearchList().isEmpty()) && removedSearch.active) {
            group.getSearchList().get(0).setActive(true);
        }
    }

}
