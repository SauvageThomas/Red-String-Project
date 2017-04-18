package model.entities;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class QTILSearchEngine extends SearchEngine {

	public QTILSearchEngine(QTILConfiguration settings) {
		super(settings);
	}

	@Override
	public int indexText() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int indexImage() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int indexAudio() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public List<String> searchByKeywords(List<Keyword> keyWords) {
		List<String> results = new ArrayList<>();
		return results;
	}

	@Override
	public List<String> searchByColor(int r, int g, int b) {
		List<String> results = new ArrayList<>();
		//TODO: 
		return results;
	}

	@Override
	public List<String> searchByShadeOfGrey(int shadeOfGrey) {
		List<String> results = new ArrayList<>();
		//TODO: 
		return results;
	}

	@Override
	public List<String> searchByFile(String filePath) {
		List<String> results = new ArrayList<>();
		//TODO: 
		return results;
	}

	@Override
	public void submitSettings() throws IOException {
		// TODO Auto-generated method stub
		
	}

}
