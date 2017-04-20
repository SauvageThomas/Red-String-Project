package model.entities;

public class PathParameter extends SearchParameter{

	private static final long serialVersionUID = 3508585461188370035L;
	
	private String filePath;

	public PathParameter(String filePath) {
		super();
		this.filePath = filePath;
	}

	@Override
	public String getString() {
		return "File (" + this.filePath + ")";
	}

	@Override
	public boolean hasError() {
		return (this.filePath == "");
	}
	
	@Override
	public String getMessageError() {
		if (this.filePath == "")
			return "Empty filepath !";
		return super.getMessageError();
	}
}
