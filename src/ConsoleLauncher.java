package src;

import src.controller.ControllerSoftware;
import src.view.console.ViewMainMenu;

public class ConsoleLauncher {

	private ViewMainMenu menu;
	
	public ConsoleLauncher() {
		ControllerSoftware controllerSoftware = new ControllerSoftware();
		this.menu = new ViewMainMenu(controllerSoftware);
	}
	
	public void start(){
		this.menu.showView();
	}

	public static void main(String[] args) {
		ConsoleLauncher console = new ConsoleLauncher();
		console.start();
	}
}
