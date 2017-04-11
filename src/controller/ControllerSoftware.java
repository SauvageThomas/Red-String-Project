package src.controller;

import java.util.Map;

import src.model.entities.QTILSoftware;
import src.model.entities.SearchEngine;
import src.model.entities.history.Request;

public class ControllerSoftware {

	private QTILSoftware software;
	
	public ControllerSoftware() {
		this.software = QTILSoftware.getSoftware();
	}

	public Map<String, SearchEngine> getEngines() {
		return this.software.getEngines();
	}

	public Request searchByKeywords(String keywords) {
		return this.software.searchByKeywords(keywords);
	}

	public void searchByShadeOfGray(int gray) {
		this.software.searchByShadeOfGray(gray);
	}

	public void searchByColor(int red, int green, int blue) {
		this.software.searchByColor(red, green, blue);
	}

	public void searchByFile(String filePath) {
		this.software.searchByFile(filePath);
	}

	public boolean loginAsAdmin(String password) {
		return this.software.loginAsAdmin(password);
	}
}
