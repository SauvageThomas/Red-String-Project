package model.entities;

import java.io.IOException;

public class DataBaseManagement {

	private CheckDataBase checkDataBase; 
	
	public DataBaseManagement(String dataBasePath, boolean mode) throws IOException {
		this.checkDataBase = new CheckDataBase(dataBasePath, mode);
		if (mode){
			this.runCheckDataBase();
		}
	}
	
	public void updateMode(boolean mode){
		if (this.checkDataBase.getMode() != mode){
			if (mode)
				this.runCheckDataBase();
			else
				this.stopCheckDataBase();
		}
	}
	
	private void runCheckDataBase() {
		this.checkDataBase.setModeOpen(true);
		this.checkDataBase.start();
	}
	
	private void stopCheckDataBase(){
		this.checkDataBase.setModeOpen(false);
	}
}
