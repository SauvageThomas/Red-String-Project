package model.entities.history;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class History implements Serializable {

	private static final long serialVersionUID = -71436115086375235L;
	private static History instance = History.load();
	private static final String path = "../assets/private/.history";

	private List<Request> requests;

	private History() {
		this.requests = new ArrayList<>();
		this.save();
	}

	public void addRequest(Request request) {
		this.requests.add(request);
		this.save();
	}

	public List<Request> getRequests() {
		return this.requests;
	}

	public static History getInstance() {
		return History.instance;
	}

	private static History load() {
		FileInputStream fileIn;
		try {
			fileIn = new FileInputStream(History.path);

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
			e.printStackTrace();
		}
		return new History();
	}

	public void save() {
		try {
			FileOutputStream fileOut = new FileOutputStream(History.path);
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(this);
			out.close();
			fileOut.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
