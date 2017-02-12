package src.view.tools;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

public enum Configuration {

	INSTANCE;

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
			List<String> lines = Arrays.asList(this.names[0] + " " + this.dataPath,
					this.names[1] + " " + this.descriptorPath, this.names[2] + " " + String.valueOf(this.windowSize),
					this.names[3] + " " + String.valueOf(this.barNumber),
					this.names[4] + " " + String.valueOf(this.quantification));
			Path file = Paths.get(".config");
			Files.write(file, lines, Charset.forName("UTF-8"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
