package model.entities;

import java.io.IOException;
import java.util.List;

import model.tools.Path;

public class QTILSearchEngine extends SearchEngine {

	private QTILKernel kernel; // Wrapper des fonctions du noyau C (JNI)
	private KeywordSearcher keywordSearcher;
	private ImageColorFinder colorSearcher;
	
	public QTILSearchEngine(QTILConfiguration settings) {
		super(settings);
		this.kernel = QTILKernel.getInstance();
		this.keywordSearcher = new KeywordSearcher();
		this.colorSearcher = new ImageColorFinder(Path.QTIL_IMAGE_INDEX);
	}

	// Index les fichiers textes (JNI)
	@Override
	public int indexText() {
		return this.kernel.updateTextDescriptors(0);
	}

	// Index les fichiers images (JNI)
	@Override
	public int indexImage() {
		return this.kernel.updateImageDescriptors(0);
	}

	// Index les fichiers sons (JNI)
	@Override
	public int indexSound() {
		return this.kernel.updateSoundDescriptors(0);
	}

	// Recherche par mots clés
	@Override
	public List<String> searchByKeywords(List<Keyword> keywords) {
		return this.keywordSearcher.searchByKeywords(keywords);
	}

	// Recherche par couleur
	@Override
	public List<String> searchByColor(int r, int g, int b) {
		return this.colorSearcher.searchImageColor(r, g, b, Integer.valueOf(this.getSettingValue("PIXEL MARGIN")));
	}

	// Recherche par gris
	@Override
	public List<String> searchByShadeOfGrey(int shadeOfGrey) {
		return this.colorSearcher.searchByShadeOfGrey(shadeOfGrey, Integer.valueOf(this.getSettingValue("PIXEL MARGIN")));
	}

	// Recherche par fichier (JNI)
	@Override
	public List<String> searchByFile(String filePath) {
		List<String> results = this.kernel.searchByFile(filePath);
		
		// Si le fichier est de type son, le noyau renvoie le flag -4, on peut alors simuler le résultat
		if (results.size() == 1 && results.get(0).equals("-4"))
			results.add(this.getSettingValue("DATA BASE") + "corpus_m.wav");
		return results;
	}
	
	// valide les settings dans un fichier de config
	@Override
	public void submitSettings() throws IOException {
		this.getSettings().submitSettings();
	}
	
	// Retourne la valeur d'un parametre
	private String getSettingValue(String key){
		return this.getSettings().getSettingValue(key);
	}

}
