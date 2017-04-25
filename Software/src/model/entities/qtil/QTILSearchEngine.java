package model.entities.qtil;

import java.io.IOException;
import java.util.List;

import model.entities.Keyword;
import model.entities.QTILKernel;
import model.entities.SearchEngine;

public class QTILSearchEngine extends SearchEngine {

	private QTILKernel kernel;
	private KeywordSearcher keywordSearcher;
	
	public QTILSearchEngine(QTILConfiguration settings) {
		super(settings);
		this.kernel = QTILKernel.getInstance();
		this.keywordSearcher = new KeywordSearcher();
		
		System.out.print("TEXT  INDEXATION...");
		int res_txt = this.indexText();
		System.out.println("  Done ! (flag = " + res_txt + ")");
		
		System.out.print("IMAGE INDEXATION...");
		int res_img = this.indexImage();
		System.out.println("  Done ! (flag = " + res_img + ")");
		
		System.out.print("SOUND  INDEXATION...");
		int res_sound = this.indexAudio();
		System.out.println("  Done ! (flag = " + res_sound + ")");
	}

	@Override
	public int indexText() {
		return this.kernel.updateTextDescriptors(1);
	}

	@Override
	public int indexImage() {
		return this.kernel.updateImageDescriptors(1);
	}

	@Override
	public int indexAudio() {
		return this.kernel.updateSoundDescriptors(1);
	}

	@Override
	public List<String> searchByKeywords(List<Keyword> keywords) {
		return this.keywordSearcher.searchByKeyword(keywords);
	}

	@Override
	public List<String> searchByColor(int r, int g, int b) {
		return ImageColorFinder.searchImageColor(r, g, b);
	}

	@Override
	public List<String> searchByShadeOfGrey(int shadeOfGrey) {
		return ImageColorFinder.searchByShadeOfGrey(shadeOfGrey);
	}

	@Override
	public List<String> searchByFile(String filePath) {
		return this.kernel.searchByFile(filePath);
	}

	@Override
	public void submitSettings() throws IOException {
		// TODO Auto-generated method stub
		
	}

}
