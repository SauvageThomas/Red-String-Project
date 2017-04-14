package view;

import java.io.IOException;

import controller.ControllerHistory;
import controller.ControllerSoftware;
import view.console.ViewMainMenu;

public class ConsoleLauncher {

	private ViewMainMenu menu;

	public ConsoleLauncher() throws IOException {
		ControllerSoftware controllerSoftware = new ControllerSoftware();
		ControllerHistory controllerHistory = new ControllerHistory();
		this.menu = new ViewMainMenu(controllerSoftware, controllerHistory);
	}

	public void start() {
		this.menu.showView();
	}

	public static void main(String[] args) {
		try {
			ConsoleLauncher console = new ConsoleLauncher();
			console.start();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
