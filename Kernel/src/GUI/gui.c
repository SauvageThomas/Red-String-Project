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
#include "functions.h"
#include "../search_engine.h"

void start_gui() {

	int action; 
	char buffer[2];
	int admin = 0;

	Config config = load_config();

	puts("\nBienvenue sur le moteur de recherche !");

	while (action != 0) {
		puts("\n================================================================");
		puts("=     *         *          MAIN  MENU          *         *     =");
		puts("================================================================");
		puts("|  1 - Demarrer une recherche                                  |"); 
		puts("|  2 - Voir les fichiers presents dans la base de donnees      |");
		puts("|  3 - Modifier la configuration du programme                  |");

		if (!admin) {
			puts("|  3 - Se connecter en tant qu'administrateur                  |");
		} else {
			puts("|  3 - Modifier la configuration du programme                  |");
			puts("|  4 - Voir les statistiques de performance                    |");
			puts("|  5 - Changer le mot de passe                                 |");
		}
		puts("|--------------------------------------------------------------|");
		puts("|  0 - Quitter                                                 |");
		puts("================================================================");

		get_input(buffer, &action);

		switch (action) {
		case 0:
			puts("Au revoir !");
			exit(EXIT_SUCCESS);
		case 1:
			launch_search_engine(config);
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

void search_gui(Config config) {
	int action;
	char buffer[2];

	puts("Veuillez choisir le mode de recherche");

	while (action != 0) {
		puts("\n================================================================");
		puts("=     *         *       SEARCH SELECTION       *         *     =");
		puts("================================================================");
		puts("|  1 - Par mot-cle                                             |");
		puts("|  2 - Par fichier equivalent                                  |");
		puts("|--------------------------------------------------------------|");
		puts("|  0 - Retour                                                  |");
		puts("================================================================");
		
		get_input(buffer, &action);

		switch (action) {
		case 0:
			return;
		case 1:
			search_by_keyword();
			break;
		case 2:
			search_by_file(get_value_of(config, "path"));
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

