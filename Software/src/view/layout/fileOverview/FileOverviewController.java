package view.layout.fileOverview;

import javafx.fxml.FXML;
import view.layout.ViewController;

public abstract class FileOverviewController extends ViewController {

	@FXML
	protected String fileName;

	public void setFile(String fileName) {
		this.fileName = fileName;
		this.init();
	}

	protected abstract void init();
}
