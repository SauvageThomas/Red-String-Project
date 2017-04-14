package view.layout.fileOverview;

import javafx.fxml.FXML;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class ImageOverviewController extends FileOverviewController {

	@FXML
	private ImageView imageView;

	@Override
	protected void init() {
		Image image = new Image("file:" + this.fileName);
		
		this.imageView.setImage(image);

		System.out.println(image.getWidth() + "*" + image.getWidth());
		System.out.println("wut");
	}

}
