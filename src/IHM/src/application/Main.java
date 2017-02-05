package application;

import java.io.IOException;

import application.view.TreeController;
import application.view.fileOverview.FileOverviewController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class Main extends Application {

	private Stage primaryStage;
	private BorderPane rootLayout;

	@Override
	public void start(Stage primaryStage) {
		this.primaryStage = primaryStage;
		this.primaryStage.setTitle("Red-String-Project");

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
			TreeController controller = loader.getController();
			controller.setController(this, primaryStage);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		launch(args);
	}

	/**
	 * Shows the file overview.
	 */
	public void showFileOverview(String path) {
		try {
			
			// Load person overview.
			FXMLLoader loader = new FXMLLoader();

			switch (path.split("\\.")[1]) {
			case "xml":
				loader.setLocation(this.getClass().getResource("view/fileOverview/TextOverview.fxml"));
				break;
			case "jpg":
				loader.setLocation(this.getClass().getResource("view/fileOverview/ImageOverview.fxml"));
				break;
			case "bmp":
				loader.setLocation(this.getClass().getResource("view/fileOverview/ImageOverview.fxml"));
				break;
			case "wav":
				System.out.println("Wip ! but later do nothing ...");
				break;
			}

			AnchorPane fileOverview = (AnchorPane) loader.load();

			// Create the dialog Stage.
			Stage fileStage = new Stage();
			fileStage.setTitle(path.split("/")[1]);
			fileStage.initModality(Modality.WINDOW_MODAL);
			fileStage.initOwner(primaryStage);
			Scene scene = new Scene(fileOverview);
			fileStage.setScene(scene);

			// Give the controller access to the main app.
			FileOverviewController controller = loader.getController();
			controller.setController(this, fileStage);
			controller.setFile(path);

			// Show the dialog and wait until the user closes it
			fileStage.showAndWait();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
