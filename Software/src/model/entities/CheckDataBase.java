package model.entities;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class CheckDataBase extends Thread {

	private boolean run;
	private File directory;
	private Map<String, Long> files;

	public CheckDataBase(String path, boolean run) throws IOException {
		this.files = new HashMap<>();
		this.setDataBaseLocation(path);
		this.fillFiles();
		this.run = run;
	}

	@Override
	public void run() {
		do {
			if (this.hasDataBaseChanged()){
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
	
	private boolean hasDataBaseChanged(){
		String[] dataFiles = this.directory.list();
		if (this.files.size() != dataFiles.length)
			return true;
		for(String name : dataFiles){
			if (!this.files.containsKey(name))
				return true;
			long date = new File(this.directory.getPath() + "/" + name).lastModified();
			if (this.files.get(name) != date)
				return true;
		}
		return false;
	}
	
	private void fillFiles() {
		this.files.clear();
		for(String name : this.directory.list()){
			this.files.put(name, new File(this.directory.getPath() + "/" + name).lastModified());
		}
	}

	public void setDataBaseLocation(String path) throws IOException {
		File directory = new File(path);
		if (!this.directory.exists())
			throw new IOException("DATABASE location not found : " + path);
		this.directory = directory;
		
	}

	public void setModeOpen(boolean mode){
		this.run = mode;
	}
	public void alertDataBaseHasChanged(){
		//TODO : Observer to respect MVC
		System.out.println("[WARNING] : data base has changed !");
	}

	public boolean getMode() {
		return this.run;
	}

	public File getFileFromDataBase(String filePath) throws IOException {
		String path = this.directory.getPath() + "/" + filePath;
		if(!this.files.containsKey(path))
			throw new IOException("File not found : " + path);
		return new File(path);
	}
}
