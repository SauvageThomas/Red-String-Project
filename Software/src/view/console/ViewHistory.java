package view.console;

import java.util.List;
import java.util.Scanner;

import controller.ControllerHistory;
import model.entities.Request;
import model.entities.Result;

public class ViewHistory extends ViewMenu {

	private ControllerHistory controllerHistory;
	private Scanner sc;

	public ViewHistory(ControllerHistory controllerHistory) {
		this.controllerHistory = controllerHistory;
		this.sc = new Scanner(System.in);
	}

	@Override
	public void showMenuItems() {
		List<Request> requests = this.controllerHistory.getSavedRequests();
		System.out.println("|     *    *     REQUEST  HISTORY     *    *     |");
		if (requests.isEmpty()) {
			System.out.println("|                                                |");
			System.out.println("|                NO REQUEST SAVED                |");
			System.out.println("|                                                |");
		} else {
			for (int i = 0; i < requests.size(); i++) {
				System.out.println("|                                                |");
				System.out.println("|  " + (i + 1) + "  -  " + requests.get(i).getSearchParameter().getStringConsole());
			}
		}
	}

	@Override
	public void applyChoice(int choice) {
		if (choice > 0 && choice <= this.controllerHistory.getSavedRequests().size()){
			Request request = this.controllerHistory.getSavedRequests().get(choice-1);
			this.showRequest(request);
		}
	}

	private void showRequest(Request request) {
		System.out.println("==================================================");
		System.out.println("|     *    *    *     REQUEST     *    *    *    |");
		System.out.println("|  SEARCH PARAMETER : " + request.getSearchParameter().getString());
		System.out.println("|------------------------------------------------|");
		System.out.println("|     *    *    *      RESULT     *    *    *    |");
		System.out.println("|                                                |");
		if (request.hasError()){
			System.out.println("|  " + request.getMessageError());
		}
		else{
			List<Result> results = request.getResults();
			for (int i = 0; i < results.size(); i++){
				System.out.println("|   [" + (i+1) + "]  " + results.get(i).toString());
			}
		}
		System.out.println("|                                                |");
		System.out.println("|------------------------------------------------|");
		System.out.println("|  1  -  PRESS ANY KEY                           |");
		System.out.println("==================================================");
		System.out.println("\n>> ");
		this.sc.nextLine();
	}

}
