package src.view.layout;

import java.io.IOException;

import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;

public class SearchBarController extends ViewController {

	@FXML
	private TextField searchField;

	public SearchBarController() {
		// TODO Auto-generated constructor stub
	}

	@FXML
	private void initialize() {

	}

	@FXML
	private void handleSearch(Event event) {
		try {
			FXMLLoader loader = new FXMLLoader();
			loader.setLocation(this.getClass().getResource("SearchOverview.fxml"));
			AnchorPane tabContent = (AnchorPane) loader.load();
			
			System.out.println(this.main);
			this.main.addTab(this.searchField.getText(), tabContent);
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

}
