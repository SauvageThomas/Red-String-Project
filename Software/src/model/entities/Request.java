package model.entities;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Request implements Serializable {

	private static final long serialVersionUID = -1953258854190134665L;

	private SearchParameter searchParameter;
	private List<Result> results;
	private int flag;

	public Request(SearchParameter searchParameter) {
		this.searchParameter = searchParameter;
		this.results = new ArrayList<Result>();
		this.flag = 0;
	}

	// Getter du paramètre de recherche
	public SearchParameter getSearchParameter() {
		return this.searchParameter;
	}

	// Ajoute un résultat à la requête
	public void addResult(Result result) {
		if (this.results.contains(result))
			this.results.get(this.results.indexOf(result)).addScore(result.getScore());
		else
			this.results.add(result);
		Collections.sort(this.results);
	}

	// Setter du flag d'erreur
	public void setFlag(int flag) {
		this.flag = flag;
	}

	// Getter des résultats
	public List<Result> getResults() {
		return this.results;
	}

	// Permet de savoir si une erreur a eue lieu
	public boolean hasError() {
		return (this.searchParameter.hasError() || this.flag <= 0);
	}

	// Récupère le message d'erreur en fonction du flag
	public String getMessageError() {
		if (this.flag == -1)
			return "File does not exist !";
		if (this.flag == -2)
			return "File is empty !";
		if (this.flag == -3)
			return "File type not supported !";
		if (this.flag == 0)
			return "No results found !";
		return this.searchParameter.getMessageError();
	}

}
