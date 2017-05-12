package model.entities;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import model.tools.Path;

public class History implements Serializable {

	private static final long serialVersionUID = -71436115086375235L;
	private static History instance = History.load();

	private List<Request> requests;

	private History() {
		this.requests = new ArrayList<>();
		this.save();
	}

	// Ajoute une requette à l'historique
	public void addRequest(Request request) {
		this.requests.add(request);
		this.save();
	}

	// Getter des requêtes
	public List<Request> getRequests() {
		return this.requests;
	}

	// Implémentation du singleton
	public static History getInstance() {
		return History.instance;
	}

	// Charge l'historique à partir du fichier .history
	private static History load() {
		FileInputStream fileIn;
		try {
			fileIn = new FileInputStream(Path.HISTORY);

			ObjectInputStream in = new ObjectInputStream(fileIn);
			History output = (History) in.readObject();
			in.close();
			fileIn.close();
			return output;
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			// First generation, no need to worry
		} catch (IOException e) {
		}
		return new History();
	}

	// Sauvegarde l'historique dans le fichier .history
	public void save() {
		try {
			FileOutputStream fileOut = new FileOutputStream(Path.HISTORY);
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(this);
			out.close();
			fileOut.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
