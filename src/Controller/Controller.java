package src.Controller;

public class Controller {
	
	private static final Controller controller = new Controller();
	
	private native void search_by_file(Object config);
	private native void update_descriptors(Object config);
	private native void error_config_file();
	private native void search_by_keyword(String keyword);
	private native void modif_config();
	private native void generate_all_descriptors(Object config);
	private native void reset_config();
	private native Object load_config();
	private native void change_password();
	private native int login();
	
	static{
		//System.loadLibrary("");
	}
	
	public static void searchByFile(Object config){
		controller.search_by_file(config);
	}
	
	public static void updateDescriptors(Object config){
		controller.update_descriptors(config);
	}
	
	public static void errorConfigFile(Object config){
		controller.error_config_file();
	}
	
	public static void searchByKeyword(String keyword){
		controller.search_by_keyword(keyword);
	}
	
	public static void modifConfig(){
		controller.modif_config();
	}
	
	public static void generateAllDescriptors(Object config){
		controller.generate_all_descriptors(config);
	}
	
	public static void resetConfig(){
		controller.reset_config();
	}
	
	public static Object loadConfig(){
		return controller.load_config();
	}
	
	public static void changePassword(){
		controller.change_password();
	}
	
	public static int loginAsAdmin(){
		return controller.login();
	}
	//public native void display_data_base();
	//public native void remove_path();
	//public native void get_value_of();

	//public native void wip();
	//public native void input_error();
	//public native void xor_crypt();
	//public native void get_input();
	//public native void clear_console();
	//public native void chrono();
	
	public static void main(String[] args) {
		
	}
}
