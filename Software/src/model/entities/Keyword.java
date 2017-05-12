package model.entities;

import java.io.Serializable;

public class Keyword implements Comparable<Keyword>, Serializable {

	private static final long serialVersionUID = -6627808384967036984L;

	private String word;
	private boolean isPositive;

	public Keyword(String word, boolean isPositive) {
		this.word = word;
		this.isPositive = isPositive;
	}

	// Getter du mot-cle
	public String getWord() {
		return this.word;
	}

	// Getter de la polarite de mot-cle
	public boolean isPositive() {
		return this.isPositive;
	}

	// Getter de la version textuelle du mot-cle
	@Override
	public String toString() {
		if (this.isPositive)
			return "+" + this.word;
		return "-" + this.word;
	}

	// Permet de voir si deux mots-cl�s sont �quivalents
	@Override
	public boolean equals(Object obj) {
		// System.out.println(word + " | " +obj);
		if (obj instanceof String && this.word.equals(obj.toString()))
			return true;
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
	
	
	// Permet de comparer deux mots cles en fonction de leur polarite et de leur
	// ordre alphabetique
	@Override
	public int compareTo(Keyword o) {
		if (this.isPositive && !o.isPositive)
			return -1;
		if (!this.isPositive && o.isPositive)
			return 1;
		return this.word.compareTo(o.word);
	}

}
