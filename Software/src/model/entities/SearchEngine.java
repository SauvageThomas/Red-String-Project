package model.entities;

public abstract class SearchEngine implements SearchEngineInterface{
	
	private Settings settings;
	
	public SearchEngine(Settings settings) {
		this.settings = settings;
	}

	public Settings getSettings() {
		return this.settings;
	}
	
	public void changeSetting(String key, String value){
		this.settings.changeSetting(key, value);
	}

	public void changeDataBaseLocation(String path){
		this.getSettings().changeDataBaseLocation(path);
	}
}
