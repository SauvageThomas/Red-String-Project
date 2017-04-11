package src;

import src.controller.ControllerHistory;
import src.controller.ControllerSoftware;
import src.view.console.ViewMainMenu;

public class ConsoleLauncher {

	private ViewMainMenu menu;

	public ConsoleLauncher() {
		ControllerSoftware controllerSoftware = new ControllerSoftware();
		ControllerHistory controllerHistory = new ControllerHistory();
		this.menu = new ViewMainMenu(controllerSoftware, controllerHistory);
	}

	public void start() {
		this.menu.showView();
	}

	public static void main(String[] args) {
		ConsoleLauncher console = new ConsoleLauncher();
		console.start();
	}
}
