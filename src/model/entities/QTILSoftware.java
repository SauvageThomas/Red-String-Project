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
		this.adminManagement = new AdminManagement();
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

	public Request searchByShadeOfGray(int gray) {
		ColorParameter colorParameter = new ColorParameter(gray);
		Request request = new Request(colorParameter);
		for (String key : this.engines.keySet()){
			List<String> results = this.engines.get(key).searchByShadeOfGrey(gray);
			for (int i = 0; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public Request searchByColor(int red, int green, int blue) {
		ColorParameter colorParameter = new ColorParameter(red, green, blue);
		Request request = new Request(colorParameter);
		for (String key : this.engines.keySet()){
			List<String> results = this.engines.get(key).searchByColor(red, green, blue);
			for (int i = 0; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public Request searchByFile(String filePath) {
		PathParameter pathParameter = new PathParameter(filePath);
		Request request = new Request(pathParameter);
		for (String key : this.engines.keySet()){
			List<String> results = this.engines.get(key).searchByFile(filePath);
			for (int i = 0; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public boolean loginAsAdmin(String password) {
		return this.adminManagement.loginAsAdmin(password);
	}
}
