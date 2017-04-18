package model.entities;

public class QTILKernel {
	
	private static QTILKernel instance;
	
	private native int update_text_descriptors(int force);
	private native int update_image_descriptors(int force);
	private native int update_sound_descriptors(int force);
	private native String[] search_by_file(String path);
	private native String[] search_by_keyword(String[] keywords);
	private native int login(String password);
	
	private QTILKernel() {
		System.loadLibrary("qtil");
	}
	
	public static QTILKernel getInstance(){
		if (instance == null)
			instance = new QTILKernel();
		return instance;
	}
	
	public String[] searchByFile(String path){
		return search_by_file(path);
	}
	
	public int updateTextDescriptors(int force){
		return update_text_descriptors(force);
	}
	
	public int updateImageDescriptors(int force){
		return update_image_descriptors(force);
	}
	
	public int updateSoundDescriptors(int force){
		return update_sound_descriptors(force);
	}
	
	public String[] searchByKeyword(String[] keywords){
		return search_by_keyword(keywords);
	}
	
	public boolean loginAsAdmin(String password){
		return (login(password) == 0);
	}
}
