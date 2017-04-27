package model.entities;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observer;

import model.entities.history.Request;
import model.entities.history.Result;
import model.tools.Path;

public class QTILSoftware {

	private static QTILSoftware software;
	private Map<String, SearchEngine> engines;
	private AdminManagement adminManagement;
	private DataBaseManagement dataBaseManagement;
	private SoftwareSettings settings;

	private QTILSoftware() throws IOException {
		this.engines = new HashMap<String, SearchEngine>();
		this.settings = new SoftwareSettings(Path.SOFTWARE_SETTINGS, "Global");
		this.adminManagement = new AdminManagement(Path.PASSWORD);
		this.dataBaseManagement = new DataBaseManagement(this.getDataBaseLocation(), true);
	}

	public static QTILSoftware getSoftware() throws IOException {
		if (software == null)
			software = new QTILSoftware();
		return software;
	}

	public List<Settings> getAllSettings(){
		List<Settings> res = new ArrayList<>();
		res.add(this.settings);
		for (String key : this.engines.keySet()){
			res.add(this.engines.get(key).getSettings());
		}
		return res;
	}
	public boolean isAdmin(){
		return this.adminManagement.isAdmin();
	}

	public void changeDataBaseLocation(String path) throws IOException{
		this.dataBaseManagement.changeDataBaseLocation(path);
		this.engines.get("QTIL").changeDataBaseLocation(path);
	}

	public File getFileFromDataBase(String filePath) throws IOException{
		return this.dataBaseManagement.getFileFromDataBase(filePath);
	}

	public void stop(){
		this.dataBaseManagement.updateMode(false);
	}

	public void addEngine(String name, SearchEngine engine){
		this.engines.put(name, engine);
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
			if (results.size() > 0)
				request.setFlag(Integer.valueOf(results.get(0)));
			for (int i = 1; i < results.size(); i++){
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
			request.setFlag(results.size());
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
			request.setFlag(results.size());
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
			if (results.size() > 0)
				request.setFlag(Integer.valueOf(results.get(0)));
			request.setFlag(Integer.valueOf(results.get(0)));
			for (int i = 1; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public boolean loginAsAdmin(String password) {
		return this.adminManagement.loginAsAdmin(password);
	}

	public void setObserver(Observer o) {
		this.dataBaseManagement.setObserver(o);
	}

	public String getDataBaseLocation() {
		return this.settings.getSettingValue("DATA BASE");
	}

	public void changeSetting(String key, String value) throws IOException {
		if (key.equals("DATA BASE"))
			this.changeDataBaseLocation(value);
		this.settings.changeSetting(key, value);
	}
	
	public void submitSettings() throws IOException{
		this.settings.submitSettings();
		for (String name : this.engines.keySet()){
			this.engines.get(name).submitSettings();
		}
	}
}
