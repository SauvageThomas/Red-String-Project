package controller;


import java.io.IOException;
import java.util.Map;

import model.entities.QTILSoftware;
import model.entities.SearchEngine;
import model.entities.history.Request;
import model.entities.qtil.QTILConfiguration;
import model.entities.qtil.QTILSearchEngine;

public class ControllerSoftware {

	private QTILSoftware software;
	
	public ControllerSoftware() throws IOException {
		this.software = QTILSoftware.getSoftware();
		this.software.addEngine("QTIL", new QTILSearchEngine(new QTILConfiguration()));
	}

	public Map<String, SearchEngine> getEngines() {
		return this.software.getEngines();
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
}
