package model.entities.qtil;

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

import model.entities.Keyword;

public class KeywordSearcher {

	private final String indexPath = "../assets/engines/QTIL/descriptors/text_index"; // temporaire

	public List<String> searchByKeyword(List<Keyword> keywords) {
		Map<String, Integer> results = new HashMap<String, Integer>();

		File file = new File(this.indexPath);
		int length = 0;
		try {
			InputStream ips = new FileInputStream(file);
			InputStreamReader ipsr = new InputStreamReader(ips);
			BufferedReader br = new BufferedReader(ipsr);
			String value = null;
			int cpt = 0;
			while ((value = br.readLine()) != null) {
				while (value != null && !value.startsWith(">")) {
					value = br.readLine();

				}
				if (value == null) {
					break;
				}
				// cpt += 1;
				if (cpt == 250) {
					System.exit(0);
				}
				// System.out.println(value);
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

	public static void main(String[] args) {
		ArrayList<Keyword> arrayList = new ArrayList<>();
		arrayList.add(new Keyword("musique", true));
		arrayList.add(new Keyword("environnement", true));
		arrayList.add(new Keyword("groupe", false));

		KeywordSearcher keywordSearcher = new KeywordSearcher();
		List<String> results = keywordSearcher.searchByKeyword(arrayList);

		for(String c : results){
			System.out.println(c);
		}
	}

}
