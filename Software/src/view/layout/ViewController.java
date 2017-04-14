package src.view.layout;

import src.DesktopLauncher;

public abstract class ViewController {

	protected DesktopLauncher main;

	public ViewController() {
		this.main = DesktopLauncher.instance;
	}

	public void setController(DesktopLauncher main) {
		this.main = DesktopLauncher.instance;
	}

}
