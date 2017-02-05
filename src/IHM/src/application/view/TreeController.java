package application.view;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

import application.Main;
import javafx.fxml.FXML;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.scene.input.MouseEvent;

public class TreeController extends ViewController {

	@FXML
	private TreeView<String> treeView;

	public TreeController() {
		System.out.println("const");
	}

	/**
	 * Initializes the controller class. This method is automatically called
	 * after the fxml file has been loaded.
	 */
	@FXML
	private void initialize() {
		System.out.println("init");

		TreeItem<String> root = new TreeItem<String>("Database");
		root.setExpanded(true);

		TreeItem<String> textItem = new TreeItem<>("Texts");
		TreeItem<String> imageItem = new TreeItem<>("Images");
		TreeItem<String> soundItem = new TreeItem<>("Sounds");

		root.getChildren().add(textItem);
		root.getChildren().add(imageItem);
		root.getChildren().add(soundItem);

		try (Stream<Path> paths = Files.walk(Paths.get("data"))) {
			paths.forEach(filePath -> {
				if (Files.isRegularFile(filePath)) {
					System.out.println(filePath);

					String path = filePath.toString().split("\\\\")[1];

					switch (path.split("\\.")[1]) {
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
				path = "data/" + path;

				System.out.println(path);
				this.main.showFileOverview(path);
			}
		}
	}
}
