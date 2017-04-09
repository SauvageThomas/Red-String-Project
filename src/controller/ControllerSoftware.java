package src.controller;

import java.util.Map;

import src.model.entities.QTILSoftware;
import src.model.entities.SearchEngine;

public class ControllerSoftware {

	private QTILSoftware software;
	
	public ControllerSoftware() {
		this.software = QTILSoftware.getSoftware();
	}

	public Map<String, SearchEngine> getEngines() {
		return this.software.getEngines();
	}

	public void searchByKeywords(String keywords) {
		this.software.searchByKeywords(keywords);
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
}
