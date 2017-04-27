package model.entities;

public class PathParameter extends SearchParameter {

	private static final long serialVersionUID = 3508585461188370035L;

	private String filePath;
	private FileType type;

	public PathParameter(String filePath) {
		super();
		this.filePath = filePath;
		this.type = this.setFileType();
	}

	public FileType getType(){
		return this.type;
	}

	private FileType setFileType() {
		FileType type = FileType.NONE;
		String copy = new String(this.filePath);
		if (copy.isEmpty())
			return type;
		String extension = copy.substring(copy.length() - 4);
		switch(extension){
		case ".xml" :
			type = FileType.TEXT;
			break;
		case ".jpg" :
			type = FileType.IMAGE;
			break;
		case ".bmp" :
			type = FileType.IMAGE;
			break;
		case ".wav" :
			type = FileType.AUDIO;
			break;
		}
		return type;
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
