package model.entities;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class SoftwareSettings extends Settings {

	public SoftwareSettings(String path, String name) throws IOException {
		super(path, name);
		this.fillSettings();
	}

	// charge le fichier de configuration et stock chaque champ dans une Map
	@Override
	public void fillSettings() throws IOException {
		FileReader fr = new FileReader(new File(this.configFilePath));
		BufferedReader br = new BufferedReader(fr);
		String line = br.readLine();
		this.addSetting("DATA BASE", new PathSetting(this.extractSettingValue(line, "path")));
		line = br.readLine();
		String[] choices = {"open", "close"};
		this.addSetting("MODE", new RadioSetting(this.extractSettingValue(line, "mode"), choices));
	}

	// extrait la valeur d'un champ dans une ligne de fichier de configuration
	private String extractSettingValue(String line, String key) throws IOException{
		if (line == null)
			throw new IOException("Empty setting file : " + this.configFilePath + " (loading setting : " + key + ")");
		return line.split(" ")[1].replace("\n\r", "");
	}
	
	// Retourne la chaine de caractere � �crire dans le fichier de config
	@Override
	public String getConfigText() {
		String res = "path " + this.getSettingValue("DATA BASE");
		res += "\nmode " + this.getSettingValue("MODE");
		return res;
	}

	@Override
	public void changeDataBaseLocation(String path) {
		this.changeSetting("DATA BASE", path);
	}

}
