package application.view;

import application.Main;
import javafx.stage.Stage;

public abstract class ViewController {

	protected Main main;
	protected Stage stage;

	public void setController(Main main, Stage stage) {
		this.main = main;
		this.stage = stage;
	}
}
