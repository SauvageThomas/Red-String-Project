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
	public int indexSound() {
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
		List<String> results = this.kernel.searchByFile(filePath);
		if (results.size() == 1 && results.get(0).equals("-4"))
			results.add(this.getSettings().getSettingValue("DATA BASE") + "corpus_m.wav");
		return results;
	}
	
	@Override
	public void submitSettings() throws IOException {
		// TODO Auto-generated method stub
		
	}

}
