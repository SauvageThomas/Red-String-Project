package model.entities;

public abstract class SearchEngine implements SearchEngineInterface{
	
	private Settings settings;
	
	public SearchEngine(Settings settings) {
		this.settings = settings;
	}

	// Retourne les parametres du moteur de recherche
	public Settings getSettings() {
		return this.settings;
	}
	
	// Modifie un parametre
	public void changeSetting(String key, String value){
		this.settings.changeSetting(key, value);
	}

	// change le chemin vers la base de données
	public void changeDataBaseLocation(String path){
		this.getSettings().changeDataBaseLocation(path);
	}
}
