package model.entities;

public class RadioSetting extends Setting {

	private String[] choices;
	
	public RadioSetting(String value, String[] choices) {
		super(value);
		this.choices = choices;
	}
	
	public String[] getChoices(){
		return this.choices;
	}

}
