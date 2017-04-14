package src.model.entities;

public class Password {

	private String passFile;
	private String backupFile;
	private String password;
	
	public Password() {
		this.passFile = ".pass";
		this.backupFile = ".backup";
		this.password = this.load();
	}

	private String load() {
		// TODO Auto-generated method stub
		return null;
	}
	
	public void change(String password) {
		this.password = password;
		// TODO Auto-generated method stub
	}
	
	public void reset(){
		// TODO Auto-generated method stub
	}
	
	public boolean compare(String password){
		return this.password.equals(password);
	}
}
