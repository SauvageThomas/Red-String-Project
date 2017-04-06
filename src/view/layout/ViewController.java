package src.view.layout;

import src.view.Main;

public abstract class ViewController {

	protected Main main;

	public ViewController() {
		this.main = Main.instance;
	}

	public void setController(Main main) {
		this.main = Main.instance;
	}

}
