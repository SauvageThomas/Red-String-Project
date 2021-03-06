package controller;


import java.io.IOException;
import java.util.List;
import java.util.Observer;

import model.entities.QTILConfiguration;
import model.entities.QTILSearchEngine;
import model.entities.QTILSoftware;
import model.entities.Request;
import model.entities.Settings;

public class ControllerSoftware {

	private QTILSoftware software;
	
	public ControllerSoftware() throws IOException {
		// on r�cup�re l'instance unique du logiciel (QTILSoftware.java)
		this.software = QTILSoftware.getSoftware();
		// on charge la configuration du moteur QTIL
		QTILConfiguration config = new QTILConfiguration(this.software.getDataBaseLocation());
		// on cr�� et ajoute le moteur QTIL au logiciel
		this.software.addEngine("QTIL", new QTILSearchEngine(config));
	}
	
	public int indexText(){
		return this.software.indexText();
	}
	
	public int indexImage(){
		return this.software.indexImage();
	}
	
	public int indexSound(){
		return this.software.indexSound();
	}
		
	
	public List<Settings> getAllSettings() {
		return this.software.getAllSettings();
	}

	public Request searchByKeywords(String keywords) {
		return this.software.searchByKeywords(keywords);
	}

	public Request searchByShadeOfGray(int gray) {
		return this.software.searchByShadeOfGray(gray);
	}

	public Request searchByColor(int red, int green, int blue) {
		return this.software.searchByColor(red, green, blue);
	}

	public Request searchByFile(String filePath) {
		return this.software.searchByFile(filePath);
	}

	public boolean loginAsAdmin(String password) {
		return this.software.loginAsAdmin(password);
	}

	public boolean isAdmin() {
		return this.software.isAdmin();
	}

	public void setObserver(Observer o) {
		this.software.setObserver(o);
	}
	
	public void stop(){
		this.software.stop();
	}
	
	public void changeSetting(String key, String value) throws IOException{
		this.software.changeSetting(key, value);
	}

	public void submitSettings(String name) throws IOException {
		this.software.submitSettings(name);
	}
}
