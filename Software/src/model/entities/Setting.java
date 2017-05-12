package model.entities;

public abstract class Setting{
	/**
	 * TODO comment
	 */
	protected String value;
	
	public Setting(String value) {
		this.value = value;
	}
	
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
