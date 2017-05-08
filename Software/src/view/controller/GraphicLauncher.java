/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import javax.swing.event.EventListenerList;

import controller.ControllerSoftware;
import javafx.application.Application;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 *
 * @author mathieu
 */
public class GraphicLauncher extends Application {
	
	private final EventListenerList listeners = new EventListenerList();
	
	private static GraphicLauncher graphicLauncher;
	private Scene scene;
	private ControllerBase baseController;
	
	public GraphicLauncher(){
		graphicLauncher = this;
	}
	
	public static GraphicLauncher getInstance(){
		if (graphicLauncher == null) {
			graphicLauncher = new GraphicLauncher();
		}
		return graphicLauncher;
	}
	
    @Override
    public void start(Stage stage) throws Exception {
        final FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/view/fxml/FXMLBase.fxml"));
        final ControllerSoftware controllerSoftware = new ControllerSoftware();
        baseController = new ControllerBase(controllerSoftware);
        controllerSoftware.setObserver(baseController);
        fxmlLoader.setController(baseController);
        final Parent root = fxmlLoader.load();

        scene = new Scene(root);
        
        stage.setScene(scene);
        stage.setMinWidth(800);
        stage.setMinHeight(600);
        stage.setTitle("QTIL Browser");
        stage.show();
        stage.setWidth(800);
        stage.setHeight(600);
        
        stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            public void handle(WindowEvent t) {
                controllerSoftware.stop();
            }
        });
        
        scene.widthProperty().addListener(new InvalidationListener(){
			@Override
			public void invalidated(Observable observable) {
				for (ResizeListener resizeListener : listeners.getListeners(ResizeListener.class)) {
					resizeListener.onResize();
				}
			}           
        });
    }
    
    public void setResizeListener (ResizeListener listener) {
        listeners.add(ResizeListener.class, listener);
    }
    
    public Scene getScene(){
    	return scene;
    }
    
    public ControllerBase getBaseController(){
    	return baseController;
    }
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

}
