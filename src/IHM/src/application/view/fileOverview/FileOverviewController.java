package application.view.fileOverview;

import application.view.ViewController;
import javafx.fxml.FXML;

public abstract class FileOverviewController extends ViewController {

	@FXML
	protected String fileName;

	public void setFile(String fileName) {
		this.fileName = fileName;
		
		this.init();
	}

	protected abstract void init();
}
