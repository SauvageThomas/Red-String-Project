package src.model.entities;

public class ColorParameter extends SearchParameter{

	private static final long serialVersionUID = -1984832989914079583L;
	
	private int r, g, b;
	private boolean isGray;
	
	
	public ColorParameter(int r, int g, int b) {
		super();
		this.r = r;
		this.g = g;
		this.b = b;
		this.isGray = false;
	}

	public ColorParameter(int gray) {
		this(gray, gray, gray);
		this.isGray = true;
	}

	@Override
	public String toString() {
		if (this.isGray)
			return "Shade of Gray : " + this.r;
		return "RGB Color : " + this.r + ", " + this.g + ", " + this.b;
	}

}
