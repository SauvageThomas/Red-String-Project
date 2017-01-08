/*
 * gui.c
 *
 *  Created on: 6 janv. 2017
 *      Author: Thomas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gui.h"

void start_gui() {

	int action;
	char buffer[2];
	int admin = 0;

	load_config();

	puts("Bienvenue sur le moteur de recherche !");

	while (action != 0) {
		puts("1 - Démarrer une recherche");
		puts("2 - Voir les fichiers présents dans la base de données");
		if (!admin) {
			puts("3 - Se connecter en tant qu'administrateur");
		} else {
			puts("3 - Modifier la configuration du programme");
			puts("4 - Voir les statistiques de performance");
			puts("5 - Changer le mot de passe");
		}
		puts("0 - Quitter");
		printf(">>");

		/*
		 while (1) { //While the input is not correct
		 if (fgets(buffer, sizeof(buffer), stdin)) {
		 if (sscanf(buffer, "%d", &action) == 1) {
		 break; //The input is correct
		 } else {
		 purge_buffer();
		 puts("Erreur, il ne faut entrer qu'un seul chiffre.");
		 }
		 }
		 }*/
		get_input(buffer, &action);
		//puts("a");
		//purge_buffer();
		//puts("d");
		//printf("Correct : <%s> et : %d", buffer, action);

		switch (action) {
		case 0:
			puts("Au revoir !");
			exit(EXIT_SUCCESS);
		case 1:
			launch_search_engine();
			break;
		case 2:
			wip();
			break;
		case 3:
			if (!admin) {
				admin = login();
			} else {
				config_gui();
			}
			break;
		case 4:
			if (admin) {
				wip();
			} else {
				input_error(buffer);
			}
			break;
		case 5:
			if (admin) {
				wip();
			} else {
				input_error(buffer);
			}
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

void search_gui() {
	int action;
	char buffer[2];

	puts("Veuillez choisir le mode de recherche");

	while (action != 0) {
		puts("1 - Par mot-clé");
		puts("2 - Par fichier équivalent");
		puts("0 - Retour");
		printf(">>");

		get_input(buffer, &action);

		switch (action) {
		case 0:
			return;
		case 1:
			search_by_keyword();
			break;
		case 2:
			search_by_file();
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

void config_gui() {

	int action;
	char buffer[2];

	puts("Bienvenue sur dans la configuration du programme !");

	while (action != 0) {
		puts("1 - Modifier le fichier de configuration");
		puts("2 - Remettre les paramètres initiaux");
		puts("0 - Retour");
		printf(">>");

		get_input(buffer, &action);

		/*
		 while (1) { //While the input is not correct
		 if (fgets(buffer, sizeof(buffer), stdin)) {
		 if (sscanf(buffer, "%d", &action) == 1) {
		 break; //The input is correct
		 } else {
		 purge_buffer();
		 puts("Erreur, il ne faut entrer qu'un seul chiffre.");
		 }
		 }
		 }*/
		//purge_buffer();
		switch (action) {
		case 0:
			break;
		case 1:
			modif_config();
			break;
		case 2:
			wip();
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

