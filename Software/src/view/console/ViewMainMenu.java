package view.console;

import java.util.Observable;
import java.util.Observer;

import controller.ControllerHistory;
import controller.ControllerSoftware;
import model.entities.CheckDataBase;

public class ViewMainMenu extends ViewMenu implements Observer{

	private ViewSearchMenu viewSearchMenu;
	private ViewHistory viewHistory;
	private ViewSettings viewSettings;
	private ViewLogin viewLogin;
	private ControllerSoftware controllerSoftware;

	public ViewMainMenu(ControllerSoftware controllerSoftware, ControllerHistory controllerHistory) {
		this.viewSearchMenu = new ViewSearchMenu(controllerSoftware, controllerHistory);
		this.viewHistory = new ViewHistory(controllerHistory);
		this.viewSettings = new ViewSettings(controllerSoftware);
		this.viewLogin = new ViewLogin(controllerSoftware);
		this.controllerSoftware = controllerSoftware;
		this.controllerSoftware.setObserver(this);
	}

	@Override
	public void showMenuItems() {
		System.out.println("|  1  -  SEARCH                                  |");
		System.out.println("|  2  -  HISTORY                                 |");  
		if (this.controllerSoftware.isAdmin())
			System.out.println("|  3  -  SETTINGS                                |");
		else
			System.out.println("|  3  -  LOGIN AS ADMIN                          |");
	}

	@Override
	public void applyChoice(int choice){

		switch (choice){
		case 1 :
			this.viewSearchMenu.showView();
			break;
		case 2 :
			this.viewHistory.showView();
			break;
		case 3 :
			if (this.controllerSoftware.isAdmin())
				this.viewSettings.showView();
			else
				this.viewLogin.showView();
			break;
		case 0 :
			this.controllerSoftware.stop();
			break;
		}
	}

	@Override
	public void update(Observable from, Object obj) {
		if (from instanceof CheckDataBase)
			System.out.println("[WARNING] : data base has changed !");
	}
}
