package model.entities;

import java.io.Serializable;

public class Result implements Comparable<Result>, Serializable {

	private static final long serialVersionUID = -8366225309691907514L;

	private String filePath;
	private int score;

	public Result(String filePath, int score) {
		this.filePath = filePath.split(" ")[0];
		this.score = score;
	}

	// Ajoute un score � un r�sultat
	public void addScore(int value) {
		this.score += value;
	}

	// Getter du chemin du r�sultat
	public String getFilePath() {
		return this.filePath;
	}

	// Getter du score
	public int getScore() {
		return this.score;
	}

	// Permet de comparer deux r�sultats en fonction de leur score
	@Override
	public int compareTo(Result other) {
		return Integer.compare(other.score, this.score);
	}

	// Permet de v�rifier si deux r�sultats sont �quivalents
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Result other = (Result) obj;
		if (this.filePath == null) {
			if (other.filePath != null)
				return false;
		} else if (!this.filePath.equals(other.filePath))
			return false;
		return true;
	}

	// Retrourne la forme textuelle du r�sultat
	@Override
	public String toString() {
		return this.filePath + " : " + this.score;
	}
}
