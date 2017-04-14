package view.console;

import controller.ControllerHistory;
import controller.ControllerSoftware;

public class ViewMainMenu extends ViewMenu{
	
	private ViewSearchMenu viewSearchMenu;
	private ViewHistory viewHistory;
	private ViewSettings viewSettings;
	private ViewLogin viewLogin;
	
	public ViewMainMenu(ControllerSoftware controllerSoftware, ControllerHistory controllerHistory) {
		this.viewSearchMenu = new ViewSearchMenu(controllerSoftware, controllerHistory);
		this.viewHistory = new ViewHistory(controllerHistory);
		this.viewSettings = new ViewSettings(controllerSoftware);
		this.viewLogin = new ViewLogin(controllerSoftware);
	}

	@Override
	public void showMenuItems() {
		System.out.println("|  1  -  SEARCH                                  |");
		System.out.println("|  2  -  HISTORY                                 |");
		System.out.println("|  3  -  SETTINGS                                |");
		System.out.println("|  4  -  LOGIN AS ADMIN                          |");
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
			this.viewSettings.showView();
			break;
		case 4 :
			this.viewLogin.showView();
			break;
		}
	}
}
