package src.model.entities;

public class Keyword {

	private String word;
	private boolean isPositive;
	
	public Keyword(String word, boolean isPositive) {
		this.word = word;
		this.isPositive = isPositive;
	}

	public String getWord() {
		return this.word;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Keyword other = (Keyword) obj;
		if (this.isPositive != other.isPositive)
			return false;
		if (this.word == null) {
			if (other.word != null)
				return false;
		} else if (!this.word.equals(other.word))
			return false;
		return true;
	}

	
}
