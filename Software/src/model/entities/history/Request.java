package model.entities.history;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import model.entities.SearchParameter;

public class Request implements Serializable{

	private static final long serialVersionUID = -1953258854190134665L;

	private SearchParameter searchParameter;
	private List<Result> results;

	public Request(SearchParameter searchParameter) {
		this.searchParameter = searchParameter;
		this.results = new ArrayList<Result>();
	}

	public String getSearchParameter() {
		return this.searchParameter.getString();
	}

	public void addResult(Result result){
		if (this.results.contains(result))
			this.results.get(this.results.indexOf(result)).addScore(result.getScore());
		else
			this.results.add(result);
		Collections.sort(this.results);
	}
	
	public List<Result> getResults() {
		return this.results;
	}

}
