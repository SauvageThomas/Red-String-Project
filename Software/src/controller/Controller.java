package controller;

public class Controller {
	
	private static final Controller controller = new Controller();
	
	private native int update_text_descriptors(int force);
	private native int update_image_descriptors(int force);
	private native int update_sound_descriptors(int force);
	private native String[] search_by_file(String path);
	private native String[] search_by_keyword(String[] keywords);
	private native int login(String password);
	
	static{
		System.loadLibrary("kernel");
	}
	
	public static String[] searchByFile(String path){
		return controller.search_by_file(path);
	}
	
	public static int updateTextDescriptors(int force){
		return controller.update_text_descriptors(force);
	}
	
	public static int updateImageDescriptors(int force){
		return controller.update_image_descriptors(force);
	}
	
	public static int updateSoundDescriptors(int force){
		return controller.update_sound_descriptors(force);
	}
	
	public static String[] searchByKeyword(String[] keywords){
		return controller.search_by_keyword(keywords);
	}
	
	public static int loginAsAdmin(String password){
		return controller.login(password);
	}
}
