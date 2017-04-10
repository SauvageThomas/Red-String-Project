package src.model.entities;

import java.util.ArrayList;
import java.util.List;

public class Request {

	private SearchParameter searchParameter;
	private List<String> results;
	
	public Request(SearchParameter searchParameter) {
		this.searchParameter = searchParameter;
		this.results = new ArrayList<String>();
	}
	
	public String getSearchParameter() {
		return this.searchParameter.toString();
	}
	
	public void addResult(String result){
		this.results.add(result);
	}

}
