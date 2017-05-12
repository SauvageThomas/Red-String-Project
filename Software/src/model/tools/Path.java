package model.tools;

public class Path {

	// ----------------------------------------------------------------------
	// ASSETS DIRECTORY
	private static final String ASSETS = "../assets/";
		
	// ----------------------------------------------------------------------
	// PRIVATE SOFTWARE PATHS
	private static final String PRIVATE = ASSETS + "private/";
	// Software config
	public static final String SOFTWARE_SETTINGS = PRIVATE + ".config";
	// Software history
	public static final String HISTORY = PRIVATE + ".history";
	// Software password
	public static final String PASSWORD = PRIVATE + ".pass";

	// ----------------------------------------------------------------------
	// ENGINES LOCATION PATH
	public static final String ENGINES = ASSETS + "engines/";
	
	// ----------------------------------------------------------------------
	// QTIL PATHS
	public static final String QTIL = ENGINES + "QTIL/";
	// QTIL config
	public static final String QTIL_SETTINGS = QTIL + ".config";
	// QTIL image index
	public static final String QTIL_IMAGE_INDEX = QTIL + "descriptors/image_index";
	// QTIL text index
	public static final String QTIL_TEXT_INDEX = QTIL + "descriptors/text_index";
}
