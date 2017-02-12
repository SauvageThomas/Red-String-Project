package src.view.layout.settings;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.AnchorPane;
import src.view.layout.ViewController;

public class RootSettingsOverviewController extends ViewController {
	
	@FXML
	private Button okButton;
	@FXML
	private Button cancelButton;
	
	@FXML
	private ScrollPane scrollPane;

	public RootSettingsOverviewController() {
		// TODO Auto-generated constructor stub
	}
	
	@FXML
	private void initialize(){
		
	}
	
	public void init(AnchorPane pane){
		this.scrollPane.setContent(pane);
	}
	
	@FXML
	private void saveHandler(){
		this.main.saveSettings();
	}
	
	@FXML
	private void cancelhandler(){
		this.main.quitSettings();
	}

}
