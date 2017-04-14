package view.layout.fileOverview;

import com.sun.org.apache.xerces.internal.parsers.SAXParser;

import javafx.beans.binding.Bindings;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import model.entities.Article;
import model.tools.SAXHandler;

public class TextOverviewController extends FileOverviewController {

	@FXML
	private ScrollPane scrollPane;
	@FXML
	private TextFlow content;
	@FXML
	private Label title;
	@FXML
	private Label author;
	@FXML
	private Label date;
	@FXML
	private Label summary;
	@FXML
	private AnchorPane innerRightPane;

	private Article article;

	private final Color[] colors = { Color.RED, Color.AQUA, Color.BLUEVIOLET, Color.SIENNA, Color.GOLDENROD };

	@FXML
	private void initialize() {
		// Nothing for now
	}

	@Override
	protected void init() {
		System.out.println(main);
		//this.content.prefWidthProperty().bind(Bindings.add(-15, parent.widthProperty()));
		this.innerRightPane.prefWidthProperty().bind(Bindings.add(-15, this.main.getRightPane().widthProperty()));

		this.extractContent();

		// TODO: Remove the argument when the search by keyword is implemented
		this.displayFile(new String[] { "cellules", "équipe" });

	}

	private void extractContent() {
		try {
			SAXParser reader = new SAXParser();
			SAXHandler handler = new SAXHandler();

			reader.setContentHandler(handler);
			reader.parse(this.fileName);

			this.article = handler.retrieveArticle();

		} catch (Exception e) {
			System.out.println(e);
		}
	}

	private void displayFile() {
		this.displayFile(null);
	}

	private void displayFile(String[] keywords) {
		
		this.title.setText(this.article.getTitle());
		this.author.setText(this.article.getAuthor());
		this.date.setText(this.article.getDate());
		this.summary.setText(this.article.getSummary());
		
		String content = this.article.getContent();

		for (String c : content.split(" ")) {
			Text tmp = new Text(c + " ");
			if (keywords != null) {
				int i = 0;
				for (String key : keywords) {
					if (c.equals(key)) {
						tmp.setFill(this.colors[i % this.colors.length]);
						break;
					}
					i += 1;
				}
			}
			this.content.getChildren().add(tmp);
		}

	}

}
