package model.entities.qtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import model.entities.PathSetting;
import model.entities.Settings;

public class QTILConfiguration extends Settings{
	// "path", "descriptors", "taille_des_fenetres", "nombre_de_barre", "quantification"
	
	private final static String SETTING_PATH = "../assets/engines/QTIL/.config";
	
	public QTILConfiguration() throws IOException {
		super(SETTING_PATH);
	}

	@Override
	public void fillSettings() throws IOException {
		FileReader fr = new FileReader(new File(this.configFilePath));
		BufferedReader br = new BufferedReader(fr);
		String line = br.readLine();
		PathSetting path = new PathSetting(this.extractSettingValue(line, "path"));
		this.addSetting("PATH", path);
		
	}
	
	private String extractSettingValue(String line, String key) throws IOException{
		if (line == null)
			throw new IOException("Empty setting file : " + this.configFilePath + " (loading setting : " + key + ")");
		/*
		if (!Pattern.matches(key + " = .\n", line))
			throw new IOException("Setting not found : " + key + " (setting file : " + this.configFilePath + ")");
			*/
		return line.split(" ")[1].replace("\n\r", "");
	}

	@Override
	public String getConfigText() {
		String res = "";
		for (String key : this.settings.keySet()){
			res += key + " = " + this.settings.get(key).getValue() + "\n";
		}
		return res;
	}
}
