package application.view.fileOverview;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import application.view.ViewController;
import javafx.fxml.FXML;
import javafx.scene.control.ScrollPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;

public class TextOverviewController extends FileOverviewController {

	@FXML
	private ScrollPane scrollPane;

	@FXML
	private TextFlow content;

	@FXML
	private void initialize() {
		// Nothing for now
	}

	@Override
	protected void init() {
		String content;
		try {
			content = new String(Files.readAllBytes(Paths.get(this.fileName)));

			// this.scrollPane.setContent(new Text(content));
			for (String c : content.split(" ")) {
				Text tmp = new Text(c + " ");
				if (c.equals("cellules")) {
					tmp.setFill(Color.RED);
				}
				this.content.getChildren().add(tmp);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
