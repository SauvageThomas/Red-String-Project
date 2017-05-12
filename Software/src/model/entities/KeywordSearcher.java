package model.entities;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import model.tools.Path;

public class KeywordSearcher {
	
	//Permet de chercher les fichiers correspondants a une liste de mots-cles (avec polarite) 
	public List<String> searchByKeywords(List<Keyword> keywords) {
		Map<String, Integer> results = new HashMap<String, Integer>();

		File file = new File(Path.QTIL_TEXT_INDEX);
		int length = 0;
		try {
			InputStream ips = new FileInputStream(file);
			InputStreamReader ipsr = new InputStreamReader(ips);
			BufferedReader br = new BufferedReader(ipsr);
			String value = null;
			while ((value = br.readLine()) != null) {
				while (value != null && !value.startsWith(">")) {
					value = br.readLine();

				}
				if (value == null) {
					break;
				}
				value = value.substring(1);
				value = value.replaceAll(" ", "");

				for (Keyword keyword : keywords) {
					if (keyword.equals(value)) {
						while (!(value = br.readLine()).startsWith(">")) {
							String[] values = value.split(" ");
							int score = Integer.valueOf(values[1]);

							// If negative substract 10 to the total
							if (!keyword.isPositive()) {
								score = -score * 2;
							}

							// Add the score to the existing entry (or create
							// it)
							if (results.containsKey(keyword)) {
								results.put(values[0], score + results.get(keyword));
							} else {
								results.put(values[0], score);
							}
						}
					}
				}
			}
			br.close();
		} catch (IOException e) {
			e.printStackTrace();
		}		;
		// Add every key with a score > 0 in order to sort it later
		List<String> sortedResults = new ArrayList<>();
		for (Entry<String, Integer> entry : results.entrySet()) {
			if (entry.getValue() > 0) {
				sortedResults.add(entry.getKey());
			}
		}

		// Sort the result
		for (int i = 1; i < sortedResults.size(); i += 1) {
			for (int j = 0; j < sortedResults.size() - i; j += 1) {
				if (results.get(sortedResults.get(j)) < results.get(sortedResults.get(j + 1))) {
					String tmp = sortedResults.get(j);
					sortedResults.set(j, sortedResults.get(j + 1));
					sortedResults.set(j + 1, tmp);
				}
			}
		}

		length = sortedResults.size();
		sortedResults.add(0, String.valueOf(length));
		return sortedResults;
	}
}
