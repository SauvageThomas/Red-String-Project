package src.view.layout.search;

import java.io.IOException;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.AnchorPane;
import src.view.layout.ViewController;

public class SearchOverviewController extends ViewController {
	
	@FXML
	private AnchorPane pane;
	
	private SearchBarController searchBarController;

	public SearchOverviewController() {
	}
	
	@FXML
	private void initialize(){
		this.showSearchBar();
	}

	private void showSearchBar() {
		try {
			// Load person overview.
			FXMLLoader loader = new FXMLLoader();

			loader.setLocation(this.getClass().getResource("SearchBar.fxml"));
			AnchorPane searchBar = (AnchorPane) loader.load();
			
			AnchorPane.setRightAnchor(searchBar, 0.0);
			AnchorPane.setLeftAnchor(searchBar, 0.0);
			AnchorPane.setTopAnchor(searchBar, 0.0);
			this.pane.getChildren().add(searchBar);

			// Give the controller access to the main app.
			this.searchBarController = loader.getController();
			this.searchBarController.setController(this.main);
			this.searchBarController.init();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
