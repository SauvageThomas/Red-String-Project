package src.model.entities.history;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import src.model.entities.SearchParameter;

public class Request implements Serializable{

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
	
	@Override
	public String toString() {
		String res = "==================================================\n";
		res += "|     *    *    *     REQUEST     *    *    *    |";
		res += "\n|                                                |\n";
		res += "|  SEARCH PARAMETER : " + this.searchParameter.toString();
		res += "\n|                                                |\n";
		if (this.results.isEmpty()){
			res += "|  No result found !                             |\n\n";
			res += "\n|                                                |\n";
		}
		else
			for (int i = 0; i < this.results.size(); i++){
				res += "|   [" + (i+1) + "]  " + this.results.get(i) + "\n";
			}
		res += "==================================================\n\n";
		return res;
	}

}