/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view;

import javax.swing.event.EventListenerList;

import controller.ControllerSoftware;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import view.controller.ControllerBase;
import view.controller.ControllerUpdateBD;
import view.controller.ResizeListener;

/**
 *
 * @author mathieu
 * 
 * Class created as a kind of singleton, helps any graphic class to get to the top of the chain
 */
public class GraphicLauncher extends Application {
	
	private final EventListenerList listeners = new EventListenerList();
	
	// Singleton
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
    	//Loading and binding corresponding FXML file
        final FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/view/fxml/FXMLBase.fxml"));
        final ControllerSoftware controllerSoftware = new ControllerSoftware();
        baseController = new ControllerBase(controllerSoftware);
        controllerSoftware.setObserver(baseController);
        fxmlLoader.setController(baseController);
        
        
        // Creating the update pop-up
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
        
        final Parent root = fxmlLoader.load();

        scene = new Scene(root);
        
        stage.setScene(scene);
        stage.setMinWidth(800);
        stage.setMinHeight(600);
        stage.setTitle("QTIL Browser");
        stage.show();
        stage.setWidth(800);
        stage.setHeight(600);
        
        // Stopping the app on clicking close button
        stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            public void handle(WindowEvent t) {
                controllerSoftware.stop();
            }
        });
        
        // Calling the resize listener when changing the size of the window
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
