package view;

import java.io.IOException;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import src.view.layout.RootController;
import src.view.layout.home.HomeController;
import src.view.tools.Configuration;

public class DesktopLauncher extends Application {

	public static DesktopLauncher instance;

	private final String appName = "Red-String-Project";

	private Stage primaryStage;
	private BorderPane rootLayout;

	private HomeController homeController;
	private RootController rootController;

	private boolean admin;

	private Configuration config;

	public DesktopLauncher() {
		super();
		synchronized (DesktopLauncher.class) {
			if (instance != null) {
				throw new UnsupportedOperationException(getClass() + " is singleton but constructor called more than once");
			}
			instance = this;
		}
	}

	@Override
	public void start(Stage primaryStage) {
		this.primaryStage = primaryStage;
		this.primaryStage.setTitle(this.appName);

		this.admin = false;
		this.config = Configuration.INSTANCE;

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
			this.rootLayout.setCenter(home);

			// Give the controller access to the main app.
			this.homeController = loader.getController();
			this.homeController.setController(this);

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

	public void activeAdminMode() {
		this.admin = true;
		this.rootController.displayAdminMode();
	}
	
	public boolean isAdminModeActivated() {
		return this.admin;
	}

	public void quitSettings() {
		this.rootController.quitSettings();
	}

	public void saveSettings() {
		this.rootController.saveSettings();
	}

	public void addTab(String name, Node node) {
		this.homeController.addTab(name, node);
	}

	public static void main(String[] args) {
		launch(args);
	}
}
