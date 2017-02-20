/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package src.view.layout.jfoenix;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXColorPicker;
import com.jfoenix.controls.JFXDrawer;
import com.jfoenix.controls.JFXHamburger;
import com.jfoenix.controls.JFXRadioButton;
import com.jfoenix.controls.events.JFXDrawerEvent;
import com.jfoenix.transitions.hamburger.HamburgerBasicCloseTransition;
import com.jfoenix.transitions.hamburger.HamburgerSlideCloseTransition;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.animation.TranslateTransition;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Rectangle;
import javafx.stage.FileChooser;
import javafx.util.Duration;

/**
 *
 * @author mathieu
 */
public class FXMLDocumentController implements Initializable {

    @FXML
    private JFXHamburger ham;

    @FXML
    private TextField textFieldSearch;

    @FXML
    private JFXDrawer drawer;

    @FXML
    private JFXColorPicker colorPicker;

    @FXML
    private VBox search;

    @FXML
    private JFXRadioButton textSearch;

    @FXML
    private JFXRadioButton fileSearch;

    @FXML
    private JFXRadioButton colorSearch;

    @FXML
    private JFXButton browseButton;

    @Override
    public void initialize(URL url, ResourceBundle rb) {

        try {

            final FileChooser fileChooser = new FileChooser();

            textFieldSearch.setVisible(true);
            colorPicker.setVisible(false);
            browseButton.setVisible(false);
            textSearch.setSelected(true);

            final ToggleGroup searchGroup = new ToggleGroup();
            textSearch.setUserData("text");
            textSearch.setToggleGroup(searchGroup);
            fileSearch.setUserData("file");
            fileSearch.setToggleGroup(searchGroup);
            colorSearch.setUserData("color");
            colorSearch.setToggleGroup(searchGroup);

            final HamburgerBasicCloseTransition burgerTask = new HamburgerBasicCloseTransition(ham);
            burgerTask.setRate(-1);

            final VBox tabMenu = FXMLLoader.load(getClass().getResource("TabMenu.fxml"));
            drawer.setSidePane(tabMenu);

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
				    search.toFront();
				    burgerTask.play();
				}
			});

            drawer.setOnDrawerOpening(new EventHandler<JFXDrawerEvent>() {
				@Override
				public void handle(JFXDrawerEvent e) {
				    burgerTask.setRate(1);
				    drawer.toFront();
				    burgerTask.play();
				}
			});

            browseButton.setOnAction(new EventHandler<ActionEvent>() {
				@Override
				public void handle(ActionEvent e) {
				    fileChooser.showOpenDialog(browseButton.getScene().getWindow());
				}
			});

            searchGroup.selectedToggleProperty().addListener(
                new ChangeListener<Toggle>() {
					@Override
					public void changed(ObservableValue<? extends Toggle> ov, Toggle old_toggle, Toggle new_toggle) {
					    if (searchGroup.getSelectedToggle() != null) {
					        switch(searchGroup.getSelectedToggle().getUserData().toString()){
					            case "text":
					                textFieldSearch.setVisible(true);
					                colorPicker.setVisible(false);
					                browseButton.setVisible(false);
					                break;
					            case "file":
					                textFieldSearch.setVisible(false);
					                colorPicker.setVisible(false);
					                browseButton.setVisible(true);
					                break;
					            case "color":
					                colorPicker.setVisible(true);
					                textFieldSearch.setVisible(false);
					                browseButton.setVisible(false);
					                break;
					        }
					    }
         }
				});

        } catch (IOException ex) {
            Logger.getLogger(FXMLDocumentController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

}
