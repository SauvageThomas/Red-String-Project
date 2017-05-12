package model.entities;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public abstract class Settings {
	
	private String name;
	protected Map<String, Setting> settings;
	protected String configFilePath;
	
	public Settings(String configFilePath, String name) throws IOException {
		this.name = name;
		this.configFilePath = configFilePath;
		this.settings = new HashMap<String, Setting>();
	}
	
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
		// (template méthode)
		writer.write(this.getConfigText());
		writer.close();
	}

	public Map<String, Setting> getSettings() {
		return this.settings;
	}
	
	public String getSettingValue(String name) {
		return this.settings.get(name).getValue();
	}

	public String getName() {
		return this.name;
	}

	public abstract void changeDataBaseLocation(String path);
	
	
}
