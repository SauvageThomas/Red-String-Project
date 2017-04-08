package src;

import src.view.console.ViewMainMenu;

public class ConsoleLauncher {

	private ViewMainMenu menu;
	
	public ConsoleLauncher() {
		this.menu = new ViewMainMenu();
	}
	
	public void start(){
		System.out.println("Hello World !");
		this.menu.showView();
	}

	public static void main(String[] args) {
		ConsoleLauncher console = new ConsoleLauncher();
		console.start();
	}
}
