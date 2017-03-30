package src.view.tools;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;

public enum Configuration {

	INSTANCE;

	private static final String fileName = ".config";
	private String dataPath;
	private String descriptorPath;
	private int windowSize;
	private int barNumber;
	private int quantification;
	private final String names[] = { "path", "descriptors", "taille_des_fenetres", "nombre_de_barre", "quantification" };

	Configuration() {
		try {
			String tmp = new String(Files.readAllBytes(Paths.get(".config")));
			String array[] = tmp.replace("\n", " ").replace("\r", "").split(" ");

			System.out.println(Arrays.toString(array));

			this.dataPath = array[1];
			this.descriptorPath = array[3];
			this.windowSize = Integer.valueOf(array[5]);
			this.barNumber = Integer.valueOf(array[7]);
			this.quantification = Integer.valueOf(array[9]);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public String getDataPath() {
		return dataPath;
	}

	public void setDataPath(String dataPath) {
		this.dataPath = dataPath;
	}

	public String getDescriptorPath() {
		return descriptorPath;
	}

	public void setDescriptorPath(String descriptorPath) {
		this.descriptorPath = descriptorPath;
	}

	public int getWindowSize() {
		return windowSize;
	}

	public void setWindowSize(int windowSize) {
		this.windowSize = windowSize;
	}

	public int getBarNumber() {
		return barNumber;
	}

	public void setBarNumber(int barNumber) {
		this.barNumber = barNumber;
	}

	public int getQuantification() {
		return quantification;
	}

	public void setQuantification(int quantification) {
		this.quantification = quantification;
	}

	public void save() {
		try {
			String content = this.names[0] + " " + this.dataPath + "\n" + this.names[1] + " " + this.descriptorPath
					+ "\n" + this.names[2] + " " + String.valueOf(this.windowSize) + "\n" + this.names[3] + " "
					+ String.valueOf(this.barNumber) + "\n" + this.names[4] + " " + String.valueOf(this.quantification)
					+ "\n";

			FileWriter fw = new FileWriter(Configuration.fileName);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write(content);

			bw.close();
			fw.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
