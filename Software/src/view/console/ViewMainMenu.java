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
		// le menu principale observe la base de donnée (CheckDataBase.java)
		this.controllerSoftware.setObserver(this);
		// lance l'indexation de la base de donnée (Phase 1 : projet Kernel + JNI)
		this.updateSoftware();
	}

	private void updateSoftware() {
		
		System.out.print("TEXT  INDEXATION...");
		// indexe les textes (Phase 1 : projet Kernel + JNI)
		int res_txt = this.controllerSoftware.indexText();
		System.out.println("  Done ! (file updated = " + res_txt + ")");
		
		System.out.print("IMAGE INDEXATION...");
		// indexe les images (Phase 1 : projet Kernel + JNI)
		int res_img = this.controllerSoftware.indexImage();
		System.out.println("  Done ! (file updated = " + res_img + ")");
		
		System.out.print("SOUND INDEXATION...");
		// indexe les sons (Phase 1 : projet Kernel + JNI)
		int res_sound =  this.controllerSoftware.indexSound();
		System.out.println("  Done ! (file updated = " + res_sound + ")");
		
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
			// le logiciel termine son exécution, on stop le(s) threads secondaires
			this.controllerSoftware.stop();
			System.out.println("QTIL SOftware is shutting down, please wait...");
			try {
				// 5s de délai pour l'arret des threads ( 5s = temps de repos d'un thread)
				Thread.sleep(5000);
				System.out.println("Good bye ! :)");
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			break;
		}
	}

	@Override
	public void update(Observable from, Object obj) {
		// affiche un warning lors d'un changement de la BDD (via Observer - Observable)
		if (from instanceof CheckDataBase)
			System.out.println("[WARNING] : data base has changed !");
	}
}
