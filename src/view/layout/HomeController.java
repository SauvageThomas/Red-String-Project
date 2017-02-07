package src.view.layout;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TextField;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import src.view.layout.fileOverview.FileOverviewController;

public class HomeController extends ViewController {

	@FXML
	private TreeView<String> treeView;

	@FXML
	private TextField searchField;

	@FXML
	private TabPane tabPane;

	@FXML
	private AnchorPane rightPane;

	private List<Tab> tabs;

	public HomeController() {
		System.out.println("const");
	}

	/**
	 * Initializes the controller class. This method is automatically called
	 * after the fxml file has been loaded.
	 */
	@FXML
	private void initialize() {
		System.out.println("init");

		this.tabs = new ArrayList<>();

		TreeItem<String> root = new TreeItem<String>("Database");
		root.setExpanded(true);

		TreeItem<String> textItem = new TreeItem<>("Texts");
		TreeItem<String> imageItem = new TreeItem<>("Images");
		TreeItem<String> soundItem = new TreeItem<>("Sounds");

		root.getChildren().add(textItem);
		root.getChildren().add(imageItem);
		root.getChildren().add(soundItem);

		try (Stream<Path> paths = Files.walk(Paths.get("data/FICHIER_PROJET/"))) {
			paths.forEach(filePath -> {
				if (Files.isRegularFile(filePath)) {
					

					String path = filePath.toString().replace('\\', '/');
					path = path.split("/")[2];

					String array[] = path.split("\\.");
					//path = array[0];
					System.out.println(filePath);
					if (array.length != 0) {

						System.err.println(path);
						switch (array[1]) {
						case "xml":
							textItem.getChildren().add(new TreeItem<>(path));
							break;
						case "jpg":
							imageItem.getChildren().add(new TreeItem<>(path));
							break;
						case "bmp":
							imageItem.getChildren().add(new TreeItem<>(path));
							break;
						case "wav":
							soundItem.getChildren().add(new TreeItem<>(path));
							break;
						}
					}
				}
			});
		} catch (IOException e) {
			e.printStackTrace();
		}

		treeView.setRoot(root);
	}

	@FXML
	private void handleDoubleClick(MouseEvent event) {
		if (event.getClickCount() == 2) {
			String path = this.treeView.getSelectionModel().getSelectedItem().getValue();
			// If you click on a file
			if (path.split("\\.").length > 1) {
				path = "data/FICHIER_PROJET/" + path;

				System.out.println(path);
				this.showFileOverview(path);
			}
		}
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
				loader.setLocation(this.getClass().getResource("fileOverview/TextOverview.fxml"));
				break;
			case "jpg":
				loader.setLocation(this.getClass().getResource("fileOverview/ImageOverview.fxml"));
				break;
			case "bmp":
				loader.setLocation(this.getClass().getResource("fileOverview/ImageOverview.fxml"));
				break;
			case "wav":
				System.out.println("Wip ! but later do nothing ...");
				break;
			}

			AnchorPane fileOverview = (AnchorPane) loader.load();

			this.addTab(path.split("/")[2], fileOverview);

			FileOverviewController controller = loader.getController();

			controller.setController(this.main);
			controller.setFile(path);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@FXML
	private void handleSearch(Event event) {
		try {
			FXMLLoader loader = new FXMLLoader();
			loader.setLocation(this.getClass().getResource("SearchOverview.fxml"));
			AnchorPane tabContent = (AnchorPane) loader.load();

			this.addTab(this.searchField.getText(), tabContent);
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	private void addTab(String name, Node node) {
		Tab tab = new Tab(name, node);

		this.tabPane.getTabs().add(tab);
		this.tabPane.getSelectionModel().select(tab);
		this.tabs.add(tab);
	}

	public AnchorPane getRightPane() {
		return this.rightPane;
	}
}
