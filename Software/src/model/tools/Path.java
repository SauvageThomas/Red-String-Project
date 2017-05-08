package model.tools;

public class Path {

	// ASSETS DIRECTORY
	private static final String ASSETS = "../assets/";
		
	// PRIVATE SOFTWARE PATHS
	private static final String PRIVATE = ASSETS + "private/";
	public static final String SOFTWARE_SETTINGS = PRIVATE + ".config";
	public static final String HISTORY = PRIVATE + ".history";
	public static final String PASSWORD = PRIVATE + ".pass";

	// ENGINES LOCATION PATH
	public static final String ENGINES = ASSETS + "engines/";
	
	// QTIL PATHS
	public static final String QTIL = ENGINES + "QTIL/";
	public static final String QTIL_SETTINGS = QTIL + ".config";
	public static final String QTIL_IMAGE_INDEX = QTIL + "descriptors/image_index";
}
