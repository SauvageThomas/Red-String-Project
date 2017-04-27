package model.entities.qtil;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import model.entities.BornedIntegerSetting;
import model.entities.PathSetting;
import model.entities.Settings;
import model.tools.Path;

public class QTILConfiguration extends Settings{

	private String DATA_BASE_PATH;
	
	public QTILConfiguration(String dataPath) throws IOException {
		super(Path.QTIL_SETTINGS, "QTIL");
		this.DATA_BASE_PATH = dataPath;
	}

	@Override
	public void changeDataBaseLocation(String path){
		this.DATA_BASE_PATH = path;
	}
	
	@Override
	public void fillSettings() throws IOException {
		FileReader fr = new FileReader(new File(this.configFilePath));
		BufferedReader br = new BufferedReader(fr);
		String line = br.readLine();
		//this.addSetting("DATA BASE", new PathSetting(this.extractSettingValue(line, "path")));
		line = br.readLine();
		this.addSetting("DESCRIPTORS", new PathSetting(this.extractSettingValue(line, "descriptors")));
		line = br.readLine();
		this.addSetting("WINDOW SIZE", new BornedIntegerSetting(this.extractSettingValue(line, "taille_des_fenetres"), 50, 1000));
		line = br.readLine();
		this.addSetting("LAYER NUMBER", new BornedIntegerSetting(this.extractSettingValue(line, "nombre_de_barre"), 50, 500));
		line = br.readLine();
		this.addSetting("QUANTIFICATION", new BornedIntegerSetting(this.extractSettingValue(line, "quantification"), 2, 16));
	}
	
	private String extractSettingValue(String line, String key) throws IOException{
		if (line == null)
			throw new IOException("Empty setting file : " + this.configFilePath + " (loading setting : " + key + ")");
		return line.split(" ")[1].replace("\n\r", "");
	}

	@Override
	public String getConfigText() {
		String res = "path " + this.DATA_BASE_PATH;
		res += "\ndescriptors " + this.settings.get("DESCRIPTORS");
		res += "\ntaille_des_fenetres" + this.settings.get("WINDOW SIZE");
		res += "\nombre_de_barre " + this.settings.get("LAYER NUMBER");
		res += "\nquantification" + this.settings.get("QUANTIFICATION");
		return res;
	}
}
