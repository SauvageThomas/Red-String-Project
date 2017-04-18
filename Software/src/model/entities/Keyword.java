package model.entities;

import java.io.Serializable;

public class Keyword implements Comparable<Keyword>, Serializable{

	private static final long serialVersionUID = -6627808384967036984L;
	
	private String word;
	private boolean isPositive;
	
	public Keyword(String word, boolean isPositive) {
		this.word = word;
		this.isPositive = isPositive;
	}

	public String getWord() {
		return this.word;
	}
	
	public boolean isPositive(){
		return this.isPositive;
	}

	@Override
	public String toString() {
		if (this.isPositive)
			return "+" + this.word;
		return "-" + this.word;
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

	@Override
	public int compareTo(Keyword o) {
		if (this.isPositive && !o.isPositive)
			return -1;
		if (!this.isPositive && o.isPositive)
			return 1;
		return this.word.compareTo(o.word);			
	}

	
}
