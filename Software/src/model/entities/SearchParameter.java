package model.entities;

import java.io.Serializable;

public abstract class SearchParameter implements Serializable{

	private static final long serialVersionUID = 7684673927847609651L;

	// Retourne une chaine format�e pour l'affichage graphique
	public abstract String getString() ;

	// Renvoie true si la recherche comporte une erreur sur le parametre de recherche
	public abstract boolean hasError();

	// Affiche un message d'erreur par d�faut
	public String getMessageError() {
		return "Invalid parameter (unknown error) !";
	}

	// Retourne une chaine format�e pour l'affichage console
	public abstract String getStringConsole() ;
}
