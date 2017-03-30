package src.model.entities;
import java.util.ArrayList;

public abstract class ConfigParameter<T> {
	/* ATTRIBUTS */
	protected T value;

	public ConfigParameter(T value) {
		this.value = value;
	}

	@Override
	public String toString() {
		return this.value.toString();
	}
	
	public ArrayList<T> getValues() {
		ArrayList<T> array = new ArrayList<>();
		array.add(this.value);
		return array;
	}
	public void setValue(T value) {
		this.value = value;
	}
}