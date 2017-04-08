package src.view.console;

public class ViewSearchMenu extends ViewMenu{

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
			this.searchWithShadeOfGreyView();
			break;
		case 4 :
			this.searchWithKeyWordsView();
			break;
		}
	}

	private void searchWithKeyWordsView() {
		// TODO Auto-generated method stub
		
	}

	private void searchWithShadeOfGreyView() {
		// TODO Auto-generated method stub
		
	}

	private void searchWithColorView() {
		// TODO Auto-generated method stub
		
	}

	private void searchWithFileView() {
		// TODO Auto-generated method stub
		
	}

}
