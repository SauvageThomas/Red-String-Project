/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.net.URL;
import java.util.Observable;
import java.util.Observer;
import java.util.ResourceBundle;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXDrawer;
import com.jfoenix.controls.JFXHamburger;
import com.jfoenix.controls.events.JFXDrawerEvent;
import com.jfoenix.transitions.hamburger.HamburgerBasicCloseTransition;

import controller.ControllerHistory;
import controller.ControllerSoftware;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import model.entities.CheckDataBase;

/**
 *
 * @author mathieu
 */
public class ControllerBase implements Initializable, TabListener, Observer {

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

	public ControllerBase(ControllerSoftware controllerSoftware) {
		this.controllerSoftware = controllerSoftware;
	}

	public JFXButton getSaveButton() {
		return saveButton;
	}

	@Override
	public void initialize(URL url, ResourceBundle rb) {

		controllerHistory = new ControllerHistory();

		group = new GraphicSearchGroup();
		group.setTabListener(this);

		final HamburgerBasicCloseTransition burgerTask = new HamburgerBasicCloseTransition(ham);
		burgerTask.setRate(-1);

		drawer.setSidePane(new ControllerSideMenu(controllerSoftware, group, ControllerBase.this, drawer));

		/*
		 * TranslateTransition tt = new
		 * TranslateTransition(Duration.millis(2000), text); tt.setByX(200f);
		 * tt.setCycleCount(1); tt.setAutoReverse(true);
		 */
		ham.addEventHandler(MouseEvent.MOUSE_PRESSED, new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent e) {
				ham.requestFocus();
				// burgerTask.setRate(burgerTask.getRate()*-1);
				if (drawer.isShown()) {
					drawer.close();
				} else {
					drawer.open();
				}
				// burgerTask.play();

				/*
				 * tt.play(); tt.setByX(tt.getByX()*-1);
				 */
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
		// header.setMargin(ham, new Insets(0, -50, 0, 0));
		header.setMargin(newTabButton, new Insets(0, 40, 0, 0));

		newTabButton.setOnMouseClicked(new EventHandler<MouseEvent>() {
			@Override
			public void handle(MouseEvent event) {
				GraphicSearch newSearch = new GraphicSearch(group, controllerSoftware);
				newSearch.searchTab.setTabListener(ControllerBase.this);
				group.addSearch(newSearch);
				if (drawer.isShown()) {
					drawer.close();
				}
			}
		});

		Event.fireEvent(newTabButton, new MouseEvent(MouseEvent.MOUSE_CLICKED, 0, 0, 0, 0, MouseButton.PRIMARY, 1, true,
				true, true, true, true, true, true, true, true, true, null));

		homeButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(false);
				for (GraphicSearch search : group.searchList) {
					if (search.active && search.currentRequest != null) {
						search.currentRequest = null;
						search.searchWindow.getChildren().clear();
						search.searchWindow.getChildren().add(new ControllerHomeSearch(search, controllerSoftware));
						search.searchTab.setTabText("New Tab");
						if (drawer.isShown()) {
							drawer.close();
						}
					}
				}
			}
		});

		saveButton.setVisible(false);

		saveButton.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent e) {
				for (GraphicSearch search : group.searchList) {
					if (search.active && search.currentRequest != null
							&& search.currentRequest.getResults().size() != 0) {
						controllerHistory.saveRequest(search.currentRequest);

						Stage newStage = new Stage();
						newStage.setTitle("Information");
						BorderPane s = new BorderPane();
						s.setPrefSize(200, 50);
						Text text = new Text("Tab saved.");
						text.setFont(Font.font("Helvetica", 20));
						text.setFill(Color.web("#00BAB5"));
						s.setCenter(text);
						Scene newScene = new Scene((Parent) s);
						newStage.setScene(newScene);
						newStage.show();
						/*
						 * try { Thread.sleep(1000); newStage.close(); } catch
						 * (InterruptedException e2) { // TODO Auto-generated
						 * catch block e2.printStackTrace(); }
						 */
					}
				}
			}
		});
	}

	@Override
	public void onNewTab(GraphicSearch newSearch) {
		header.getChildren().add(newSearch.searchTab);
		header.setMargin(newSearch.searchTab, new Insets(0, 90, 0, 0));
		currentWindow.getChildren().add(newSearch.searchWindow);
		GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(false);
	}

	@Override
	public void onCloseTab(GraphicSearch removedSearch) {
		header.getChildren().remove(removedSearch.searchTab);
		currentWindow.getChildren().remove(removedSearch.searchWindow);
		group.getSearchList().remove(removedSearch);
		if ((!group.getSearchList().isEmpty()) && removedSearch.active) {
			group.getSearchList().get(0).setActive(true);
			if (group.getSearchList().get(0).currentRequest != null) {
				GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(true);
			} else {
				GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(false);
			}
		} else {
			GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(false);
		}
	}

	@Override
	public void update(Observable o, Object arg) {
		if (o instanceof CheckDataBase) {
			Platform.runLater(new Runnable() {
				@Override
				public void run() {
					Stage newStage = new Stage();
					newStage.setTitle("Warning");
					ControllerUpdateBD controllerUpdate = new ControllerUpdateBD(controllerSoftware, newStage);
					
					Scene newScene = new Scene((Parent) controllerUpdate);
					newStage.setScene(newScene);
					newStage.show();
				}
			});
		}
	}

}
