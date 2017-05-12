package model.entities;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observer;

import model.tools.Path;

public class QTILSoftware {

	// Singleton
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
	
	// accès à l'instance unique
	public static QTILSoftware getSoftware() throws IOException {
		if (software == null)
			software = new QTILSoftware();
		return software;
	}

	// Retourne une liste de configurations
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

	// Change le chemin de la BDD
	public void changeDataBaseLocation(String path) throws IOException{
		// change le chemin du control de la BDD
		this.dataBaseManagement.changeDataBaseLocation(path);
		// change le chemin dans la configuration du moteur QTIL
		this.engines.get("QTIL").changeDataBaseLocation(path);
	}

	// Retourne le fichier demandé depuis la BDD
	public File getFileFromDataBase(String filePath) throws IOException{
		return this.dataBaseManagement.getFileFromDataBase(filePath);
	}

	// Stop le thread d'observation de la BDD
	public void stop(){
		this.dataBaseManagement.updateMode(false);
	}

	// Ajoute un moteur au logiciel
	public void addEngine(String name, SearchEngine engine){
		this.engines.put(name, engine);
	}

	// Retourne l'ensemble des moteurs
	public Map<String, SearchEngine> getEngines() {
		return this.engines;
	}

	public Request searchByKeywords(String keywords) {
		String[] words = keywords.split(" ");
		// On définit le parametre de recherche : ici KeywordsParameter
		KeywordsParameter keywordsParameter = new KeywordsParameter();
		for(String word : words){
			word.replace(" ", "");
			// On filtre les mots d'une taille > à 3 caracteres
			if (word.length() > 3){
				// On gère la polarité
				if (word.charAt(0) == '-')
					keywordsParameter.addKeyword(new Keyword(word.replaceFirst("-", ""), false));
				else
					keywordsParameter.addKeyword(new Keyword(word, true));
			}
		}
		// On créé la requete
		Request request = new Request(keywordsParameter);

		// On lance la recherche pour chaque moteur
		for (String key : this.engines.keySet()){
			// On récupère l'ensemble des résultats
			List<String> results = this.engines.get(key).searchByKeywords(keywordsParameter.getKeywords());
			
			// Si il y a des résultats, le flag = le bombre de résultats
			if (results.size() > 0)
				request.setFlag(Integer.valueOf(results.get(0)));
			// On créé les resultats et on les ajoute à la requete
			for (int i = 1; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public Request searchByShadeOfGray(int gray) {
		// On définit le parametre de recherche : ici ColorParameter
		ColorParameter colorParameter = new ColorParameter(gray);
		// On créé la requete
		Request request = new Request(colorParameter);
		// On lance la recherche pour chaque moteur
		for (String key : this.engines.keySet()){
			// On récupère l'ensemble des résultats
			List<String> results = this.engines.get(key).searchByShadeOfGrey(gray);
			// Si il y a des résultats, le flag = le bombre de résultats
			request.setFlag(results.size());
			// On créé les resultats et on les ajoute à la requete
			for (int i = 0; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public Request searchByColor(int red, int green, int blue) {
		// On définit le parametre de recherche : ici ColorParameter
		ColorParameter colorParameter = new ColorParameter(red, green, blue);
		// On créé la requete
		Request request = new Request(colorParameter);
		// On lance la recherche pour chaque moteur
		for (String key : this.engines.keySet()){
			List<String> results = this.engines.get(key).searchByColor(red, green, blue);
			request.setFlag(results.size());
			// On créé les resultats et on les ajoute à la requete
			for (int i = 0; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	public Request searchByFile(String filePath) {
		// On définit le parametre de recherche : ici PathParameter
		PathParameter pathParameter = new PathParameter(filePath);
		// On créé la requete
		Request request = new Request(pathParameter);
		// On lance la recherche pour chaque moteur
		for (String key : this.engines.keySet()){
			List<String> results = this.engines.get(key).searchByFile(filePath);
			if (results.size() > 0)
				request.setFlag(Integer.valueOf(results.get(0)));
			// On créé les resultats et on les ajoute à la requete
			for (int i = 1; i < results.size(); i++){
				Result result = new Result(results.get(i), results.size() - i);
				request.addResult(result);
			}
		}
		return request;
	}

	// Retourne true si la connexion est réussie
	public boolean loginAsAdmin(String password) {
		return this.adminManagement.loginAsAdmin(password);
	}

	// Assigne un observateur à la BDD
	public void setObserver(Observer o) {
		this.dataBaseManagement.setObserver(o);
	}

	// Retourne le chemin de la BDD
	public String getDataBaseLocation() {
		return this.settings.getSettingValue("DATA BASE");
	}

	// Change un parametre
	public void changeSetting(String key, String value) throws IOException {
		if (key.equals("DATA BASE")){
			this.changeDataBaseLocation(value);
			for (String key2 : this.engines.keySet()){
				this.engines.get(key2).changeSetting(key, value);
			}
		}
		this.settings.changeSetting(key, value);
	}

	// Valide les parametres et les sauvegarde dans les fichiers de config
	public void submitSettings(String name) throws IOException{
		if (name.equals("Global")){
			this.settings.submitSettings();
			for (String key : this.engines.keySet()){
				this.engines.get(key).submitSettings();
			}
		}
		else
			this.engines.get(name).submitSettings();
	}

	// Index les fichiers textes
	public int indexText() {
		int res = 0;
		for (String key : this.engines.keySet()){
			res += this.engines.get(key).indexText();
		}
		return res;
	}
	
	// Index les fichiers images
	public int indexImage() {
		int res = 0;
		for (String key : this.engines.keySet()){
			res += this.engines.get(key).indexImage();
		}
		return res;
	}
	
	// Index les fichiers sons
	public int indexSound() {
		int res = 0;
		for (String key : this.engines.keySet()){
			res += this.engines.get(key).indexSound();
		}
		return res;
	}
}
