package application.view;

import application.Main;
import javafx.stage.Stage;

public abstract class ViewController {

	protected Main main;

	public void setController(Main main) {
		this.main = main;
	}
}
