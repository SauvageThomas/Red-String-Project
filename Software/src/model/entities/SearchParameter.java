package model.entities;

import java.io.Serializable;

public abstract class SearchParameter implements Serializable{

	private static final long serialVersionUID = 7684673927847609651L;

	public abstract String getString() ;

	public abstract boolean hasError();

	public String getMessageError() {
		return "Invalid parameter (unknown error) !";
	}
}
