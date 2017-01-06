/*
 * gui.c
 *
 *  Created on: 6 janv. 2017
 *      Author: Thomas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gui.h"
#include "../Tools/data_handler.h"

char key[PASSLEN] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215, 48421, 629,
		314, 4784, 5102, 914, 213, 316, 145, 78 };

void start_gui() {

	int action;
	char buffer[2];
	int admin = 0;

	puts("Bienvenue sur le moteur de recherche !");

	while (action != 0) {
		puts("1 - Démarrer une recherche");
		puts("2 - Se connecter en tant qu'administrateur");
		puts("3 - Voir les fichiers présents dans la base de données");

		if (admin) {
			puts("4 - Modifier la configuration du programme");
			puts("5 - Voir les statistiques de performance");
		}

		puts("0 - Quitter");

		while (1) {
			if (fgets(buffer, sizeof(buffer), stdin)) {
				if (sscanf(buffer, "%d", &action) == 1) {
					break;
				} else {
					purge_buffer();
					puts("Erreur, il ne faut entrer qu'un seul chiffre.");
				}
			}
		}

		purge_buffer();

		if (admin) {
			switch (action) {
			case 4:
				wip();
				break;
			case 5:
				wip();
				break;
			}
		}

		switch (action) {
		case 0:
			exit(EXIT_SUCCESS);
		case 1:
			launch_search_engine();
			break;
		case 2:
			admin = login();
			break;
		case 3:
			wip();
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

int login() {
	char pass[PASSLEN];
	puts("What is the password ?");
	if (!fgets(pass, sizeof(pass), stdin)) {
		return 0;
	}
	strtok(pass, "\n");

	DataFile data_file = init_data_file(".pass");
	set_data_file_length(&data_file);

	//xor_crypt(pass);
	//write_string_in_file(data_file, pass);

	char* compare = read_string_from_file(data_file);

	xor_crypt(compare);

	if (!strcmp(compare, pass)) {
		puts("Vous êtes identifié en tant qu'admin !");
		return 1;
	} else {
		puts("Identification refusée.");
		return 0;
	}

}

void wip() {
	puts("WIP !");
}

void input_error(char *input) {
	printf("\"%s\" n'existe pas. Veuillez reessayer.\n", input);
}

void xor_crypt(char *password) {
	for (int i = 0; i < PASSLEN; i += 1) {
		password[i] ^= key[i];
	}
}

