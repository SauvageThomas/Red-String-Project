package model.entities;

import java.io.File;
import java.io.IOException;
import java.util.Observer;

public class DataBaseManagement {

	private CheckDataBase checkDataBase;
	private Thread thread;

	public DataBaseManagement(String dataBasePath, boolean mode) throws IOException {
		this.checkDataBase = new CheckDataBase(dataBasePath, mode);
		this.thread = new Thread(this.checkDataBase);
		if (mode) {
			this.runCheckDataBase();
		}
	}

	// Permet d'ajouter un observeur à la liste des observeurs
	public void setObserver(Observer o) {
		this.checkDataBase.addObserver(o);
	}

	// Mets à jour le mode
	public void updateMode(boolean mode) {
		if (this.checkDataBase.getMode() != mode) {
			if (mode)
				this.runCheckDataBase();
			else
				this.stopCheckDataBase();
		}
	}

	// Lanche le thread qui s'occupe de la vérification de la base de données
	private void runCheckDataBase() {
		this.checkDataBase.setModeOpen(true);
		this.thread.start();
	}

	// Change le mode du thread (le met en suspend)
	private void stopCheckDataBase() {
		this.checkDataBase.setModeOpen(false);
	}

	// Change le chemin de la base de données
	public void changeDataBaseLocation(String path) throws IOException {
		this.checkDataBase.setDataBaseLocation(path);
	}

	// Récupère le contenu d'un fichier en fonction de son chemin
	public File getFileFromDataBase(String filePath) throws IOException {
		return this.checkDataBase.getFileFromDataBase(filePath);
	}
}
