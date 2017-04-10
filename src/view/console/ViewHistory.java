package src.view.console;

import java.util.List;

import src.controller.ControllerHistory;
import src.model.entities.Request;

public class ViewHistory extends View{

	private ControllerHistory controllerHistory;
	
	public ViewHistory(ControllerHistory controllerHistory) {
		this.controllerHistory = controllerHistory;
	}
	
	@Override
	public void showView() {
		List<Request> requests = this.controllerHistory.getSavedRequests();
		System.out.println("Request history :");
		if (requests.isEmpty()){
			System.out.println(" - no request saved !");
		}
		else{
			for (Request r : requests){
				System.out.println(r.getSearchParameter());
			}
		}
	}

}
