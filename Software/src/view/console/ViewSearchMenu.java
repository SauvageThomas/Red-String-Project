package view.console;

import java.util.List;
import java.util.Scanner;

import controller.ControllerHistory;
import controller.ControllerSoftware;
import model.entities.Request;
import model.entities.Result;

public class ViewSearchMenu extends ViewMenu{

	private ControllerSoftware controllerSoftware;
	private ControllerHistory controllerHistory;
	
	public ViewSearchMenu(ControllerSoftware controllerSoftware, ControllerHistory controllerHistory) {
		this.controllerSoftware = controllerSoftware;
		this.controllerHistory = controllerHistory;
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
		Request requestResult = this.controllerSoftware.searchByKeywords(keywords);
		this.showRequestResult(requestResult, sc);
	}

	private void showRequestResult(Request requestResult, Scanner sc) {
		System.out.println("==================================================");
		System.out.println("|     *    *    *     REQUEST     *    *    *    |");
		System.out.println("|  SEARCH PARAMETER : " + requestResult.getSearchParameter().getString());
		System.out.println("|------------------------------------------------|");
		System.out.println("|     *    *    *      RESULT     *    *    *    |");
		System.out.println("|                                                |");
		if (requestResult.hasError()){
			System.out.println("|  " + requestResult.getMessageError());
		}
		else{
			List<Result> results = requestResult.getResults();
			for (int i = 0; i < results.size(); i++){
				System.out.println("|   [" + (i+1) + "]  " + results.get(i).toString());
			}
		}
		System.out.println("|                                                |");
		System.out.println("|------------------------------------------------|");
		System.out.println("|  1  -  SAVE REQUEST                            |");
		System.out.println("|  0  -  EXIT                                    |");
		System.out.println("==================================================");
		System.out.println("\n>> ");
		int choice = sc.nextInt();
		if (choice == 1)
			this.controllerHistory.saveRequest(requestResult);
	}

	private void searchWithShadeOfGrayView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter your gray value (0 - 255) :");
		System.out.println(">> ");
		int gray = sc.nextInt();
		Request requestResult = this.controllerSoftware.searchByShadeOfGray(gray);
		this.showRequestResult(requestResult, sc);
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
		Request requestResult = this.controllerSoftware.searchByColor(red, green, blue);
		this.showRequestResult(requestResult, sc);
	}

	private void searchWithFileView() {
		Scanner sc = new Scanner(System.in);
		System.out.println("Please, enter your file path :");
		System.out.println(">> ");
		String filePath = sc.nextLine();
		Request requestResult = this.controllerSoftware.searchByFile(filePath);
		this.showRequestResult(requestResult, sc);
	}

}
