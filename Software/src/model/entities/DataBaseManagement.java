package model.entities;

public class DataBaseManagement {

	private String dataBasePath;
	private boolean automaticMode;
	private Thread checkDataBase; 
	
	public DataBaseManagement(String dataBasePath, boolean mode) {
		this.dataBasePath = dataBasePath;
		this.setAutomaticMode(mode);
		this.checkDataBase = new Thread();
		if (mode){
			this.runCheckDataBase();
		}
	}
	
	private void runCheckDataBase() {
		this.checkDataBase.start();
	}

	public void setAutomaticMode(boolean mode){
		this.automaticMode = mode;
	}
}
