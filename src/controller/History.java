package src.controller;

import java.util.ArrayList;
import java.util.List;

public class History {

	private List<Request> requests;
	
	public History() {
		this.requests = new ArrayList<>();
	}
	
	public void addRequest(Request request){
		this.requests.add(request);
	}
	
	public List<Request> getRequests(){
		return this.requests;
	}
}
