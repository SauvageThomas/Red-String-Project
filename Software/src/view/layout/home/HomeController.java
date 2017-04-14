package src.view.layout.home;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

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
import src.DesktopLauncher;
import src.view.layout.ViewController;
import src.view.layout.fileOverview.FileOverviewController;
import src.view.layout.search.SearchBarController;
import src.view.tools.Configuration;

public class HomeController extends ViewController {

	@FXML
	private TreeView<String> treeView;
	@FXML
	private TextField treeField;
	@FXML
	private TabPane tabPane;
	@FXML
	private AnchorPane rightPane;
	@FXML
	private AnchorPane innerPane;

	private SearchBarController searchBarController;
	private List<Tab> tabs;

	private int nbXML;
	private int nbImage;
	private int nbAudio;
	private static int maxTreeItem = 15;

	public HomeController() {
		System.out.println("const");
	}

	/**
	 * Initializes the controller class. This method is automatically called
	 * after the fxml file has been loaded.
	 */
	@FXML
	private void initialize() {

		this.tabs = new ArrayList<>();
		this.handleTreeSearch();
		this.showSearchBar();
	}
	
	private void showSearchBar() {
		try {
			// Load person overview.
			FXMLLoader loader = new FXMLLoader();

			loader.setLocation(this.getClass().getResource("../search/SearchBar.fxml"));
			AnchorPane searchBar = (AnchorPane) loader.load();
			
			AnchorPane.setRightAnchor(searchBar, 0.0);
			AnchorPane.setLeftAnchor(searchBar, 0.0);
			AnchorPane.setBottomAnchor(searchBar, 0.0);
			this.innerPane.getChildren().add(searchBar);

			// Give the controller access to the main app.
			this.searchBarController = loader.getController();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void setController(DesktopLauncher main) {
		System.out.println(searchBarController);
		this.searchBarController.setController(this.main);
		this.searchBarController.init();
	}

	@FXML
	private void handleTreeSearch() {

		nbXML = 0;
		nbImage = 0;
		nbAudio = 0;

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

		// TODO: Link it to the config file
		try (Stream<Path> paths = Files.walk(Paths.get("data/FICHIER_PROJET/"))) {

			paths.forEach(filePath -> {
				if (Files.isRegularFile(filePath)) {

					if (filePath.toString().toLowerCase().contains(this.treeField.getText())) {
						// System.out.println(this.treeField.getText());

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
							if (nbXML > HomeController.maxTreeItem) {
								textItem.setExpanded(false);
							}
							if (nbImage > HomeController.maxTreeItem) {
								imageItem.setExpanded(false);
							}
							if (nbAudio > HomeController.maxTreeItem) {
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

				path = Configuration.INSTANCE.getDataPath() + path;
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
				loader.setLocation(this.getClass().getResource("../fileOverview/TextOverview.fxml"));
				break;
			case "jpg":
				loader.setLocation(this.getClass().getResource("../fileOverview/ImageOverview.fxml"));
				break;
			case "bmp":
				loader.setLocation(this.getClass().getResource("../fileOverview/ImageOverview.fxml"));
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

	public void addTab(String name, Node node) {
		Tab tab = new Tab(name, node);

		this.tabPane.getTabs().add(tab);
		this.tabPane.getSelectionModel().select(tab);
		this.tabs.add(tab);
	}

	public AnchorPane getRightPane() {
		return this.rightPane;
	}

}
