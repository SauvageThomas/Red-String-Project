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
		if (mode){
			this.runCheckDataBase();
		}
	}
	
	public void setObserver(Observer o){
		this.checkDataBase.addObserver(o);
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
		this.thread.start();
	}
	
	private void stopCheckDataBase(){
		this.checkDataBase.setModeOpen(false);
	}
	
	public void changeDataBaseLocation(String path) throws IOException{
		this.checkDataBase.setDataBaseLocation(path);
	}

	public File getFileFromDataBase(String filePath) throws IOException{
		return this.checkDataBase.getFileFromDataBase(filePath);
	}
}
