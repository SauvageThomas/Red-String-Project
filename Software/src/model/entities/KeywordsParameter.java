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
		res += "\n";
		for (Keyword keyword : this.keywords){
		//for(int i = 0; i < Math.min(3, keywords.size()); i++){
			if (keyword.isPositive())
			//if (keywords.get((int) i).isPositive())
				res += "\t|    +  " + keyword.getWord();
				//res += "\t|    +  " + keywords.get((int) i).getWord();
			else
				res += "\t|    -  " + keyword.getWord();
				//res += "\t|    -  " + keywords.get((int) i).getWord();
		}
		return res;
	}

	@Override
	public boolean hasError() {
		return (this.keywords.isEmpty());
	}

	@Override
	public String getMessageError() {
		if (this.keywords.isEmpty())
			return "Invalid keywords !";
		return super.getMessageError();
	}

	@Override
	public String getStringConsole() {
		String res = this.keywords.size() + " Keyword";
		if (this.keywords.size() > 1)
			res += "s";
		for (Keyword keyword : this.keywords){
			if (keyword.isPositive())
				res += "\n|        +  " + keyword.getWord();
			else
				res += "\n|        -  " + keyword.getWord();
		}
		return res;
	}
}
