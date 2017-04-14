package view.layout.search;

import java.io.IOException;

import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.Spinner;
import javafx.scene.control.SpinnerValueFactory;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.AnchorPane;
import view.layout.ViewController;

public class SearchBarController extends ViewController {

	@FXML
	private TextField searchKeywordField;
	@FXML
	private TextField searchFileField;

	@FXML
	private Button searchKeywordButton;
	@FXML
	private Button searchFileButton;
	@FXML
	private Button searchImageButton;

	@FXML
	private Button browseButton;

	@FXML
	private Spinner<Integer> spinner;
	@FXML
	private ColorPicker colorPicker;
	@FXML
	private Label sliderValue;
	@FXML
	private Slider slider;

	private EventHandler<KeyEvent> keyEventHandler;

	public SearchBarController() {
		// TODO Auto-generated constructor stub
	}

	@FXML
	private void initialize() {
	}

	public void init() {
		System.out.println("init search bar");

		this.keyEventHandler = new EventHandler<KeyEvent>() {

			@Override
			public void handle(KeyEvent keyEvent) {
				if (!Character.isDigit(keyEvent.getCharacter().charAt(0))) {
					String tmp = spinner.getEditor().getText();
					String result = "";
					for(char c : tmp.toCharArray()){
						if(Character.isDigit(c)){
							result += c;
						}
					}
					spinner.getEditor().setText(result);
				}
			}
		};

		this.spinner.addEventHandler(KeyEvent.ANY, this.keyEventHandler);

		this.spinner.setValueFactory(new SpinnerValueFactory.IntegerSpinnerValueFactory(0, 100));
		this.spinner.getValueFactory().setValue(1);
	}

	@FXML
	private void handleSearch(Event event) {
		this.showSearchOverview();
	}

	private void showSearchOverview() {
		try {
			FXMLLoader loader = new FXMLLoader();
			loader.setLocation(this.getClass().getResource("SearchOverview.fxml"));
			AnchorPane tabContent = (AnchorPane) loader.load();

			System.out.println(this.main);
			this.main.addTab(this.searchKeywordField.getText(), tabContent);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@FXML
	private void sliderHandler() {
		this.sliderValue.setText((int) this.slider.getValue() + "%");
	}

	@FXML
	private void searchImageHandler() {
		System.out.println(this.colorPicker.getValue() + " " + this.slider.getValue() + "%");
		this.showSearchOverview();
	}
}
