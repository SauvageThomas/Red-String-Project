package model.entities;

import java.io.IOException;
import java.util.List;

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
	public abstract int indexSound();

	/**
	 * TODO comment
	 **/
	public abstract List<String> searchByKeywords(List<Keyword> keyWords);

	/**
	 * TODO comment
	 **/
	public abstract List<String> searchByColor(int r, int g, int b);

	/**
	 * TODO comment
	 **/
	public abstract List<String> searchByShadeOfGrey(int shadeOfGrey);

	/**
	 * TODO comment
	 **/
	public abstract List<String> searchByFile(String filePath);

	/**
	 * TODO comment
	 **/
	public abstract void submitSettings() throws IOException;

}
