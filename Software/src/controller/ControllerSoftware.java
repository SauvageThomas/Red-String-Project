package controller;


import java.io.IOException;
import java.util.List;
import java.util.Observer;

import model.entities.QTILSoftware;
import model.entities.Settings;
import model.entities.history.Request;
import model.entities.qtil.QTILConfiguration;
import model.entities.qtil.QTILSearchEngine;

public class ControllerSoftware {

	private QTILSoftware software;
	
	public ControllerSoftware() throws IOException {
		this.software = QTILSoftware.getSoftware();
		QTILConfiguration config = new QTILConfiguration(this.software.getDataBaseLocation());
		this.software.addEngine("QTIL", new QTILSearchEngine(config));
		//this.software.addEngine("QTIL2", new QTILSearchEngine(config));
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
}
