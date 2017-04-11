package src.model.entities;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class KeywordsParameter extends SearchParameter{

	private static final long serialVersionUID = 2425640457139854637L;
	private List<Keyword> keywords;
	
	public KeywordsParameter() {
		this.keywords = new ArrayList<Keyword>();
	}
	
	public void addKeyword(Keyword keyword) {
		if (!this.keywords.contains(keyword)){
			this.keywords.add(keyword);
		}
	}

	public List<Keyword> getKeywords() {
		return this.keywords;
	}

	@Override
	public String toString() {
		Collections.sort(this.keywords);
		String res = this.keywords.size() + " Keywords";
		for (Keyword keyword : this.keywords){
			if (keyword.isPositive())
				res += "\n|  +  " + keyword.getWord();
			else
				res += "\n|  -  " + keyword.getWord();
		}
		return res;
		
	}
}
