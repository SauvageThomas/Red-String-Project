package src.model.entities;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public abstract class SearchEngineSetting {
	/* ATTRIBUTS */
	
	protected Map<String, Setting> settings;
	protected String configFilePath;
	
	/* CONSTRUCTORS */
	public SearchEngineSetting(String configFilePath) throws IOException {
		this.configFilePath = configFilePath;
		this.settings = new HashMap<>();
		this.fillSettings();
	}
	
	/* METHODS */
	/**
	 * TODO comment
	 */
	public abstract void fillSettings() throws IOException;
	
	/**
	 * TODO comment
	 */
	public abstract String getConfigText();
	
	/**
	 * TODO comment
	 */
	public void addSetting(String key, Setting s){
		this.settings.put(key, s);
	}
	
	/**
	 * TODO comment
	 */
	public void changeSetting(String key, String value){
		if (this.settings.containsKey(key)){
			this.settings.get(key).setValue(value);
		}
	}

	/**
	 * TODO comment
	 */
	public void submitSettings() throws IOException{
		FileWriter fw = new FileWriter(this.configFilePath);
		BufferedWriter writer = new  BufferedWriter(fw);
		writer.write(this.getConfigText());
		writer.close();
	}
}
