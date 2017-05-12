package model.entities;

public class BornedIntegerSetting extends Setting {

	/* ATTRIBUTS */

	private int min;
	private int max;

	/* CONSTRUCTORS */
	public BornedIntegerSetting(String value, int min, int max) {
		super(value);
		this.min = min;
		this.max = max;
	}

	/* METHODS */

	// Récupère le minimum
	public int getMin() {
		return this.min;
	}

	// Récupère le maximum
	public int getMax() {
		return this.max;
	}
}
