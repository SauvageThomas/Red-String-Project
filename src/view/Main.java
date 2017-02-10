package src.view;

import java.io.IOException;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import src.Controller.Controller;
import src.view.layout.RootController;
import src.view.layout.home.HomeController;

public class Main extends Application {
	
	private final String appName = "Red-String-Project";
	
	private Stage primaryStage;
	private BorderPane rootLayout;
	
	private HomeController homeController;
	private RootController rootController;
	
	private boolean admin;

	@Override
	public void start(Stage primaryStage) {
		this.primaryStage = primaryStage;
		this.primaryStage.setTitle(this.appName);

		this.admin = false;

		//Controller.searchByKeyword("cellule");
		// System.out.println(new File("bear.wav").toURI());
		// final AudioClip clip = new
		// AudioClip("http://wavsource.com/snds_2017-02-05_1692732105491832/animals/bear_growl_y.wav");

		// clip.play(1.0);

		// System.out.println("Playing...");

		this.initRootLayout();

		this.showHome();
	}

	/**
	 * Initializes the root layout.
	 */
	public void initRootLayout() {
		try {
			// Load root layout from fxml file.
			FXMLLoader loader = new FXMLLoader();
			loader.setLocation(this.getClass().getResource("layout/RootLayout.fxml"));
			rootLayout = (BorderPane) loader.load();

			 rootController = loader.getController();
			rootController.setController(this);

			// Show the scene containing the root layout.
			Scene scene = new Scene(rootLayout);
			primaryStage.setScene(scene);
			primaryStage.show();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Shows the home inside the root layout.
	 */
	public void showHome() {
		try {
			// Load person overview.
			FXMLLoader loader = new FXMLLoader();

			loader.setLocation(this.getClass().getResource("layout/home/HomeLayout.fxml"));
			AnchorPane home = (AnchorPane) loader.load();

			// Set person overview into the center of root layout.
			rootLayout.setCenter(home);

			// Give the controller access to the main app.
			homeController = loader.getController();
			homeController.setController(this);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public AnchorPane getRightPane() {
		return this.homeController.getRightPane();
	}
	
	public Stage getPrimaryStage() {
		return this.primaryStage;
	}

	public static void main(String[] args) {
		launch(args);
	}

	public void activeAdminMode() {
		this.admin = true;
		this.rootController.displayAdminMode();
	}
}
