package model.entities;

public class AdminManagement {

	private boolean isAdmin;
	private Password password;
	
	public AdminManagement(String path) {
		this.isAdmin = false;
		this.password = new Password(path);
	}
	
	public boolean isAdmin(){
		return this.isAdmin;
	}
	
	public boolean loginAsAdmin(String password){
		if (!this.isAdmin){
			this.isAdmin = this.password.compare(password);
		}
		return this.isAdmin;
	}
}
