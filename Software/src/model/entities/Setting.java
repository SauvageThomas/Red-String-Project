package model.entities;

public abstract class Setting{
	
	protected String value;
	
	public Setting(String value) {
		this.value = value;
	}
	
	// Retourne la valeur d'un parametre
	public String getValue(){
		return this.value;
	}
	
	// Change la valeur d'un parametre
	public void setValue(String value) {
		this.value = value;
	}
}
