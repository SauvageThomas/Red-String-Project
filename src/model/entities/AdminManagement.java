package src.model.entities;

public class AdminManagement {

	private boolean isAdmin;
	private Password password;
	
	public AdminManagement() {
		this.isAdmin = false;
		this.password = new Password();
	}
}
