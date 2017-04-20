package model.entities;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class QTILSearchEngine extends SearchEngine {

	private QTILKernel kernel;
	
	public QTILSearchEngine(QTILConfiguration settings) {
		super(settings);
		this.kernel = QTILKernel.getInstance();
		int res_txt = this.indexText();
		System.out.println("TEXT  INDEXATION : " + res_txt);
		int res_img = this.indexImage();
		System.out.println("IMAGE INDEXATION : " + res_img);
		int res_sound = this.indexAudio();
		System.out.println("SOUND INDEXATION : " + res_sound);
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
		List<String> results = new ArrayList<>();
		String[] arrayKeywords = new String[keywords.size()];
		for (int i = 0; i < keywords.size(); i++){
			arrayKeywords[i] = keywords.get(i).toString();
		}
		String[] arrayResults = this.kernel.searchByKeyword(arrayKeywords);
		for (String result : arrayResults){
			results.add(result);
		}
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
		return this.kernel.searchByFile(filePath);
	}

	@Override
	public void submitSettings() throws IOException {
		// TODO Auto-generated method stub
		
	}

}
