package src.model.entities;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import src.model.entities.history.Request;
import src.model.entities.history.Result;

public class QTILSoftware {

	private static QTILSoftware software;
	private Map<String, SearchEngine> engines;
	private AdminManagement adminManagement;

	private QTILSoftware() {
		this.engines = new HashMap<String, SearchEngine>();
		try {
			QTILConfiguration settings = new QTILConfiguration(".config");
			this.engines.put("QTIL", new QTILSearchEngine(settings));
		} catch (IOException e) {
			System.out.println("ERROR : " + e.getMessage());
			System.exit(1);
		}
	}

	public static QTILSoftware getSoftware() {
		if (software == null)
			software = new QTILSoftware();
		return software;
	}

	public Map<String, SearchEngine> getEngines() {
		return this.engines;
	}

	public Request searchByKeywords(String keywords) {
		String[] words = keywords.split(" ");
		KeywordsParameter keywordsParameter = new KeywordsParameter();
		for(String word : words){
			word.replace(" ", "");
			if (word.length() > 3){
				if (word.charAt(0) == '-')
					keywordsParameter.addKeyword(new Keyword(word.replaceFirst("-", ""), false));
				else
					keywordsParameter.addKeyword(new Keyword(word, true));
			}
		}
		Request request = new Request(keywordsParameter);
		
		for (String key : this.engines.keySet()){
			List<String> results = this.engines.get(key).searchByKeywords(keywordsParameter.getKeywords());
			for (int i = 0; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public void searchByShadeOfGray(int gray) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public void searchByColor(int red, int green, int blue) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public void searchByFile(String filePath) {
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
		// TODO Auto-generated method stub
	}

	public boolean loginAsAdmin(String password) {
		// TODO open/check password in file .pass
		return true;
	}
}
