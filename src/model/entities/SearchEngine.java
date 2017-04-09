package src.model.entities;

import java.util.Map;

public abstract class SearchEngine {
	
	private SearchEngineSetting settings;
	
	public SearchEngine(SearchEngineSetting settings) {
		this.settings = settings;
	}

	public Map<String, Setting> getSettings() {
		return this.settings.getSettings();
	}
	
	
}
