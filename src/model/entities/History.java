package src.model.entities;

import java.util.ArrayList;
import java.util.List;

public class History {

	private List<Request> requests;
	
	public History() {
		this.requests = new ArrayList<>();
		this.load();
	}
	
	public void addRequest(Request request){
		this.requests.add(request);
		this.save();
	}
	
	public List<Request> getRequests(){
		return this.requests;
	}
	
	public void load(){
		
	}
	
	public void save(){
		
	}
}
