package model.entities.history;

import java.io.Serializable;

public class Result implements Comparable<Result>, Serializable{

	private static final long serialVersionUID = -8366225309691907514L;
	
	private String filePath;
	private int score;
	
	public Result(String filePath, int score) {
		this.filePath = filePath.split(" ")[0];
		this.score = score;
	}

	public void addScore(int value){
		this.score += value;
	}
	
	public String getFilePath() {
		return this.filePath;
	}

	public int getScore() {
		return this.score;
	}
	
	@Override
	public int compareTo(Result other) {
		return Integer.compare(other.score, this.score);
	}

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

	@Override
	public String toString() {
		return this.filePath + " : " + this.score;
	}
}
