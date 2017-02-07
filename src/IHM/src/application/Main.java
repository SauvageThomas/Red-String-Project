package application;

import java.io.IOException;

import application.model.XMLHandler;
import application.view.HomeController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class Main extends Application {

	private Stage primaryStage;
	private BorderPane rootLayout;
	private HomeController homeController;

	@Override
	public void start(Stage primaryStage) {
		this.primaryStage = primaryStage;
		this.primaryStage.setTitle("Red-String-Project");
		
		new XMLHandler("data/1.xml");

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
			loader.setLocation(this.getClass().getResource("view/RootLayout.fxml"));
			rootLayout = (BorderPane) loader.load();

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

			loader.setLocation(this.getClass().getResource("view/HomeLayout.fxml"));
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

	public static void main(String[] args) {
		launch(args);
	}

}
