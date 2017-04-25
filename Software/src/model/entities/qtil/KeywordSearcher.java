package model.entities.qtil;

import java.util.ArrayList;
import java.util.List;

import model.entities.Keyword;

public class KeywordSearcher {

	private final String indexPath = "../assets/engines/QTIL/descriptors/text_index"; //temporaire
	
	public List<String> searchByKeyword(List<Keyword> keywords) {
		List<String> results = new ArrayList<String>();
		//TODO: return list of result :
		// list[0] = flag de la recherche !!!!! soit le nb de resultats, soit 0 si pblm par exemple.
		// list[1] = best result
		// "-word" = negatif
		// "word" = positif
		// keywords have > 3 chars
		return results;
	}

}
