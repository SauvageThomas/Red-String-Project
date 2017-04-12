package src.view.console;

import java.util.List;

import src.controller.ControllerHistory;
import src.model.entities.history.Request;

public class ViewHistory extends ViewMenu {

	private ControllerHistory controllerHistory;

	public ViewHistory(ControllerHistory controllerHistory) {
		this.controllerHistory = controllerHistory;
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
				System.out.println("|  " + (i + 1) + "  -  " + requests.get(i).getSearchParameter());
			}
		}
	}

	@Override
	public void applyChoice(int choice) {
		System.out.println(this.controllerHistory.getSavedRequests().get(choice-1));
	}

}
