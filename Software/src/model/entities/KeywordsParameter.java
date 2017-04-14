package model.entities;

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
		Collections.sort(this.keywords);
	}

	public List<Keyword> getKeywords() {
		return this.keywords;
	}

	@Override
	public String getString() {
		String res = this.keywords.size() + " Keyword";
		if (this.keywords.size() > 1)
			res += "s";
		for (Keyword keyword : this.keywords){
			if (keyword.isPositive())
				res += "\n|    +  " + keyword.getWord();
			else
				res += "\n|    -  " + keyword.getWord();
		}
		return res;
	}
}
