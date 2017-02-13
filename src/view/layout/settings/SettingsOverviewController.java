package src.view.layout.settings;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.MenuButton;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import src.view.layout.ViewController;
import src.view.tools.Configuration;

public class SettingsOverviewController extends ViewController {

	@FXML
	private AnchorPane rootPain;

	@FXML
	private TextField dataPath;
	@FXML
	private TextField descriptorsPath;
	@FXML
	private TextField windowsSize;
	@FXML
	private TextField barNumbers;
	@FXML
	private TextField textApp;
	@FXML
	private TextField imageApp;
	@FXML
	private TextField audioApp;

	@FXML
	private ComboBox<Integer> quantification;

	@FXML
	private Button browseDataPath;
	@FXML
	private Button browseDescPath;

	@FXML
	private MenuButton menuTextApp;
	@FXML
	private MenuButton menuImageApp;
	@FXML
	private MenuButton menuAudioApp;

	private Configuration config;

	public SettingsOverviewController() {
		this.config = Configuration.INSTANCE;
	}

	@FXML
	public void initialize() {
		this.dataPath.textProperty().set(this.config.getDataPath());
		this.descriptorsPath.textProperty().set(this.config.getDescriptorPath());

		this.quantification.getItems().addAll(1, 2, 3, 4);
		this.quantification.getSelectionModel().select(this.config.getQuantification() - 1);

		this.windowsSize.textProperty().set(String.valueOf(this.config.getWindowSize()));
		this.barNumbers.textProperty().set(String.valueOf(this.config.getBarNumber()));

		this.textApp.textProperty().set("This app");
		this.imageApp.textProperty().set("This app");
		this.audioApp.textProperty().set("This app");
		
		//If not admin don't display configuration
		if (!this.main.isAdminModeActivated()) {
			//this.configPane..getChildren().remove(0);
			//this.configPane.visibleProperty().set(false);
			this.rootPain.getChildren().remove(3);
		}

		/*
		 * this.menuTextApp.textProperty().set("This app");
		 * this.menuImageApp.textProperty().set("This app");
		 * this.menuAudioApp.textProperty().set("This app");
		 */
	}

	public void save() {
		// TODO: Check the values before doing anything
		this.config.setDataPath(this.dataPath.getText());
		this.config.setDescriptorPath(this.descriptorsPath.getText());
		this.config.setQuantification(this.quantification.getSelectionModel().getSelectedItem());
		this.config.setBarNumber(Integer.valueOf(this.barNumbers.getText()));
		this.config.setWindowSize(Integer.valueOf(this.windowsSize.getText()));

		this.config.save();
		this.main.quitSettings();
	}

}
