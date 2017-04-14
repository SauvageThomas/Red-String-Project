package view.layout;

import view.DesktopLauncher;

public abstract class ViewController {

	protected DesktopLauncher main;

	public ViewController() {
		this.main = DesktopLauncher.instance;
	}

	public void setController(DesktopLauncher main) {
		this.main = DesktopLauncher.instance;
	}

}
