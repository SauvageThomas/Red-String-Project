package model.entities;

import java.util.Map;

public abstract class SearchEngine implements SearchEngineInterface{
	
	private Settings settings;
	
	public SearchEngine(Settings settings) {
		this.settings = settings;
	}

	public Map<String, Setting> getSettings() {
		return this.settings.getSettings();
	}
	
	public void changeSetting(String key, String value){
		this.settings.changeSetting(key, value);
	}
}
