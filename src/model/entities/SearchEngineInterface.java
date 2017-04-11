package src.model.entities;

import java.io.IOException;
import java.util.ArrayList;

public interface SearchEngineInterface {

	/**
	 * TODO comment
	 **/
	public abstract int indexText();

	/**
	 * TODO comment
	 **/
	public abstract int indexImage();

	/**
	 * TODO comment
	 **/
	public abstract int indexAudio();

	/**
	 * TODO comment
	 **/
	public abstract ArrayList<String> searchByKeywords(ArrayList<KeyWord> keyWords);

	/**
	 * TODO comment
	 **/
	public abstract ArrayList<String> searchByColor(int r, int g, int b);

	/**
	 * TODO comment
	 **/
	public abstract ArrayList<String> searchByShadeOfGrey(int shadeOfGrey);

	/**
	 * TODO comment
	 **/
	public abstract ArrayList<String> searchByFile(String filePath);

	/**
	 * TODO comment
	 **/
	public abstract void submitSettings() throws IOException;

}
