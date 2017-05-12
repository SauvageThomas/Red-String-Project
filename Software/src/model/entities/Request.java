package model.entities;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Request implements Serializable{

	private static final long serialVersionUID = -1953258854190134665L;

	private SearchParameter searchParameter;
	private List<Result> results;
	private int flag;

	public Request(SearchParameter searchParameter) {
		this.searchParameter = searchParameter;
		this.results = new ArrayList<Result>();
		this.flag = 0;
	}
	
	public SearchParameter getSearchParameter(){
		return this.searchParameter;
	}

	public void addResult(Result result){
		if (this.results.contains(result))
			this.results.get(this.results.indexOf(result)).addScore(result.getScore());
		else
			this.results.add(result);
		Collections.sort(this.results);
	}
	
	public void setFlag(int flag){
		this.flag = flag;
	}
	
	public List<Result> getResults() {
		return this.results;
	}

	public boolean hasError() {
		return (this.searchParameter.hasError() || this.flag <= 0);
	}

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
