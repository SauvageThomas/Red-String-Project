package view.console;

import java.util.Scanner;

public abstract class ViewMenu extends View{

	/*
	 * Class g�n�rale d'un menu console
	 */
	
	@Override
	public void showView(){
		// m�thode g�n�rale d'affichage d'un menu et de l'application du choix
		int choice = 0;
		do{
			this.showMenu();
			choice = this.getChoice();
			// m�thode d�l�gu�e � la classe fille (template m�thode)
			this.applyChoice(choice);
		}while(choice != 0);
	}
	
	private void showMenu() {
		System.out.println("==================================================");
		System.out.println("|  Please, select your choice :                  |");
		System.out.println("==================================================");
		this.showMenuItems();
		System.out.println("|------------------------------------------------|");
		System.out.println("|  0  -  EXIT                                    |");
		System.out.println("==================================================");
	}

	private int getChoice() {
		Scanner sc = new Scanner(System.in);
		System.out.print("\n>> ");
		return sc.nextInt();
	}

	public abstract void showMenuItems();
	
	public abstract void applyChoice(int choice);
}
