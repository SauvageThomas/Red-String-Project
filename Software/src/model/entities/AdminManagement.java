package model.entities;

public class AdminManagement {

	private boolean isAdmin;
	private Password password;

	public AdminManagement(String path) {
		this.isAdmin = false;
		this.password = new Password(path);
	}

	// Permet de voir si l'utilisateur est authentifié en tant qu'administrateur
	// ou pas
	public boolean isAdmin() {
		return this.isAdmin;
	}

	// Permet de se connecter en administrateur si le mot de passe est correct
	public boolean loginAsAdmin(String password) {
		if (!this.isAdmin) {
			this.isAdmin = this.password.compare(password);
		}
		return this.isAdmin;
	}
}
