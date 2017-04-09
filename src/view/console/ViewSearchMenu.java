package src.view.console;

import java.util.Scanner;

import src.controller.ControllerSoftware;

public class ViewSearchMenu extends ViewMenu{

	private ControllerSoftware controllerSoftware;
	
	public ViewSearchMenu(ControllerSoftware controllerSoftware) {
		this.controllerSoftware = controllerSoftware;
	}
	
	@Override
	public void showMenuItems() {
		System.out.println("|  1  -  SEARCH WITH A FILE                      |");
		System.out.println("|  2  -  SEARCH WITH A COLOR                     |");
		System.out.println("|  3  -  SEARCH WITH A SHADE OF GREY             |");
		System.out.println("|  4  -  SEARCH WITH KEYWORDS                    |");
	}

	@Override
	public void applyChoice(int choice) {
		switch (choice){
		case 1 :
			this.searchWithFileView();
			break;
		case 2 :
			this.searchWithColorView();
			break;
		case 3 :
			this.searchWithShadeOfGrayView();
			break;
		case 4 :
			this.searchWithKeywordsView();
			break;
		}
	}

	private void searchWithKeywordsView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter your keywords :");
		System.out.println(">> ");
		String keywords = sc.nextLine();
		this.controllerSoftware.searchByKeywords(keywords);
	}

	private void searchWithShadeOfGrayView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter your gray value (0 - 255) :");
		System.out.println(">> ");
		int gray = sc.nextInt();
		this.controllerSoftware.searchByShadeOfGray(gray);
	}

	private void searchWithColorView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter your red value (0 - 255) :");
		System.out.println(">> ");
		int red = sc.nextInt();
		System.out.println("Please, enter your green value (0 - 255) :");
		System.out.println(">> ");
		int green = sc.nextInt();
		System.out.println("Please, enter your blue value (0 - 255) :");
		System.out.println(">> ");
		int blue = sc.nextInt();
		this.controllerSoftware.searchByColor(red, green, blue);		
	}

	private void searchWithFileView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter your file path :");
		System.out.println(">> ");
		String filePath = sc.nextLine();
		this.controllerSoftware.searchByFile(filePath);
	}

}
