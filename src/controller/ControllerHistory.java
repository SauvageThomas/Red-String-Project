package src.controller;

import java.util.List;

import src.model.entities.History;
import src.model.entities.Request;

public class ControllerHistory {

	private History history;
	
	public ControllerHistory() {
		this.history = new History();
	}
	
	public void saveRequest(Request request){
		this.history.addRequest(request);
	}
	
	public List<Request> getSavedRequests(){
		return this.history.getRequests();
	}
}
