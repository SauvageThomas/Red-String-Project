package model.entities;

public class BornedIntegerSetting extends Setting {
	/* ATTRIBUTS */
	/**
	 * TODO comment
	 */
	private int min;
	/**
	 * TODO comment
	 */
	private int max;
	
	/* CONSTRUCTORS */
	public BornedIntegerSetting(String value, int min, int max) {
		super(value);
		this.min = min;
		this.max = max;
	}
	
	/* METHODS */
	/**
	 * TODO comment
	**/
	public int getMin() {
		return this.min;
	}
	
	/**
	 * TODO comment
	**/
	public int getMax() {
		return this.max;
	}
}
