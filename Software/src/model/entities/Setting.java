package src.model.entities;

public abstract class Setting{
	/* ATTRIBUTS */
	/**
	 * TODO comment
	 */
	protected String value;
	
	/* CONSTRUCTORS */
	public Setting(String value) {
		this.value = value;
	}
	
	/* METHODS */
	/**
	 * TODO comment
	 */
	public String getValue(){
		return this.value;
	}
	
	/**
	 * TODO comment
	 */
	public void setValue(String value) {
		this.value = value;
	}
}
