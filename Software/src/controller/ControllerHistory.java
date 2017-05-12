package controller;

import java.util.List;

import model.entities.History;
import model.entities.Request;

public class ControllerHistory {

	private History history;
	
	public ControllerHistory() {
		this.history = History.getInstance();
	}
	
	public void saveRequest(Request request){
		this.history.addRequest(request);
	}
	
	public List<Request> getSavedRequests(){
		return this.history.getRequests();
	}
}
