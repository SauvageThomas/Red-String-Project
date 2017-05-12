package model.entities;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class KeywordsParameter extends SearchParameter {

	private static final long serialVersionUID = 2425640457139854637L;
	private List<Keyword> keywords;

	public KeywordsParameter() {
		this.keywords = new ArrayList<Keyword>();
	}

	// Ajoute un mot-cl� aux param�tres de recherche
	public void addKeyword(Keyword keyword) {
		if (!this.keywords.contains(keyword)) {
			this.keywords.add(keyword);
		}
		Collections.sort(this.keywords);
	}

	// Getter des mots-cl�s
	public List<Keyword> getKeywords() {
		return this.keywords;
	}

	// R�cup�re la version textuelle de l'objet
	@Override
	public String getString() {
		String res = this.keywords.size() + " Keyword";
		if (this.keywords.size() > 1)
			res += "s";
		res += "\n";
		for (Keyword keyword : this.keywords) {
			if (keyword.isPositive())
				res += "\t|    +  " + keyword.getWord();
			else
				res += "\t|    -  " + keyword.getWord();
		}
		return res;
	}

	// Permet de voir si une erreur est survenue
	@Override
	public boolean hasError() {
		return (this.keywords.isEmpty());
	}

	// R�cup�re le message d'erreur
	@Override
	public String getMessageError() {
		if (this.keywords.isEmpty())
			return "Invalid keywords !";
		return super.getMessageError();
	}

	// R�cup�re la version textuelle de l'objet (pour le mode console)
	@Override
	public String getStringConsole() {
		String res = this.keywords.size() + " Keyword";
		if (this.keywords.size() > 1)
			res += "s";
		for (Keyword keyword : this.keywords) {
			if (keyword.isPositive())
				res += "\n|        +  " + keyword.getWord();
			else
				res += "\n|        -  " + keyword.getWord();
		}
		return res;
	}
}
