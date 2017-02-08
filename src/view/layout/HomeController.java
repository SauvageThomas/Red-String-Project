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
import src.view.FilterableTreeItem;
import src.view.layout.fileOverview.FileOverviewController;

public class HomeController extends ViewController {

	@FXML
	private TreeView<String> treeView;

	@FXML
	private TextField searchField;

	@FXML
	private TextField treeField;

	@FXML
	private TabPane tabPane;

	@FXML
	private AnchorPane rightPane;

	private List<Tab> tabs;

	private int nbXML;
	private int nbImage;
	private int nbAudio;

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

		System.out.println("abxc".contains(""));

		this.tabs = new ArrayList<>();
		this.handleTreeSearch();
	}

	@FXML
	private void handleTreeSearch() {

		nbXML = 0;
		nbImage = 0;
		nbAudio = 0;

		if (this.treeField.getText() == null) {
			System.out.println("fuck it");
		}

		TreeItem<String> root = new TreeItem<String>("Database");
		root.setExpanded(true);

		TreeItem<String> textItem = new TreeItem<>("Texts");
		TreeItem<String> imageItem = new TreeItem<>("Images");
		TreeItem<String> soundItem = new TreeItem<>("Sounds");

		textItem.setExpanded(true);
		imageItem.setExpanded(true);
		soundItem.setExpanded(true);

		root.getChildren().add(textItem);
		root.getChildren().add(imageItem);
		root.getChildren().add(soundItem);

		try (Stream<Path> paths = Files.walk(Paths.get("data/FICHIER_PROJET/"))) {

			paths.forEach(filePath -> {
				if (Files.isRegularFile(filePath)) {

					if (filePath.toString().toLowerCase().contains(this.treeField.getText())) {
						System.out.println(this.treeField.getText());

						// Allows windows execution
						String path = filePath.toString().replace('\\', '/');

						path = path.split("/")[2];

						String array[] = path.split("\\.");
						// path = array[0];
						// System.out.println(filePath);

						if (array.length != 0) {

							switch (array[1]) {
							case "xml":
								textItem.getChildren().add(new TreeItem<>(path));
								nbXML += 1;
								break;
							case "jpg":
								imageItem.getChildren().add(new TreeItem<>(path));
								nbImage += 1;
								break;
							case "bmp":
								imageItem.getChildren().add(new TreeItem<>(path));
								nbImage += 1;
								break;
							case "wav":
								soundItem.getChildren().add(new TreeItem<>(path));
								nbAudio += 1;
								break;
							}
							if (nbXML > 5) {
								System.out.println("ok");
								textItem.setExpanded(false);
							}
							if (nbImage > 5) {
								imageItem.setExpanded(false);
							}
							if (nbAudio > 5) {
								soundItem.setExpanded(false);
							}
						}
					}
				}
			});
		} catch (IOException e) {
			e.printStackTrace();
		}

		this.treeView.setRoot(root);
	}

	@FXML
	private void handleDoubleClick(MouseEvent event) {
		if (event.getClickCount() == 2) {
			TreeItem<String> selection = this.treeView.getSelectionModel().getSelectedItem();
			if (selection == null)
				return;
			String path = selection.getValue();
			if (path.split("\\.").length > 1) {
				path = "data/FICHIER_PROJET/" + path;
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
				return;
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
