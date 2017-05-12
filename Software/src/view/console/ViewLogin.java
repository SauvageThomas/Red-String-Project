package view.console;

import java.util.Scanner;

import controller.ControllerSoftware;

public class ViewLogin extends View{

	private ControllerSoftware controllerSoftware;
	
	public ViewLogin(ControllerSoftware controllerSoftware) {
		this.controllerSoftware = controllerSoftware;
	}
	
	@Override
	public void showView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter the admin password :");
		System.out.println(">> ");
		String password = sc.nextLine();
		// essaye de se connecter
		boolean flag = this.controllerSoftware.loginAsAdmin(password);
		if (flag){
			System.out.println("You are now logged as admin.");
		}
		else{
			System.out.println("Wrong password !!");
		}
	}

}
