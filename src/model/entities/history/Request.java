package src.model.entities.history;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import src.model.entities.SearchParameter;

public class Request  implements Serializable{

	private static final long serialVersionUID = -1953258854190134665L;
	
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
