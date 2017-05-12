package model.entities;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Observable;

public class CheckDataBase extends Observable implements Runnable {

	private boolean run;
	private File directory;
	private Map<String, Long> files;

	public CheckDataBase(String path, boolean run) throws IOException {
		this.files = new HashMap<>();
		this.setDataBaseLocation(path);
		this.fillFiles();
		this.run = run;
	}

	// Lance le thread
	@Override
	public void run() {
		do {
			if (this.hasDataBaseChanged()) {
				this.alertDataBaseHasChanged();
				this.fillFiles();
			}
			try {
				Thread.sleep(5000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} while (this.run);
	}

	// V�rifie si la base de donn�es a chang� ou pas
	private boolean hasDataBaseChanged() {
		String[] dataFiles = this.directory.list();
		if (this.files.size() != dataFiles.length)
			return true;
		for (String name : dataFiles) {
			if (!this.files.containsKey(name))
				return true;
			long date = new File(this.directory.getPath() + "/" + name).lastModified();
			if (this.files.get(name) != date)
				return true;
		}
		return false;
	}

	// Remplis la list de fichers
	private void fillFiles() {
		this.files.clear();
		for (String name : this.directory.list()) {
			this.files.put(name, new File(this.directory.getPath() + "/" + name).lastModified());
		}
	}

	// Setter du chemin de la base de donn�es
	public void setDataBaseLocation(String path) throws IOException {
		File directory = new File(path);
		if (!directory.exists())
			throw new IOException("DATABASE location not found : " + path);
		this.directory = directory;

	}

	// Setter du bool�en du mode ouvert/ferm�
	public void setModeOpen(boolean mode) {
		this.run = mode;
	}

	// Pr�vient que la base de donn�es � chang�e et pr�vient ses observeurs
	public void alertDataBaseHasChanged() {
		this.setChanged();
		this.notifyObservers();
	}

	// Getter du mode ouvert/ferm�
	public boolean getMode() {
		return this.run;
	}

	// Permet de r�cup�rer le contenu d'un fichier en fonction de son chemin
	public File getFileFromDataBase(String filePath) throws IOException {
		String path = this.directory.getPath() + "/" + filePath;
		if (!this.files.containsKey(path))
			throw new IOException("File not found : " + path);
		return new File(path);
	}
}
