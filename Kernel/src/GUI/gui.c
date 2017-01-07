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

const char key[PASSLEN] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215,
		48421, 629, 314, 4784, 5102, 914, 213, 316, 145, 78 };

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

void config_gui() {

	int action;
	char buffer[2];

	puts("Bienvenue sur dans la configuration du programme !");

	while (action != 0) {
		puts("1 - Modifier le fichier de configuration");
		puts("2 - Remettre les paramètres initiaux");
		puts("0 - Retour");

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

void modif_config() {
	char* str = "!!";
	DataFile data_file = init_data_file(".config");
	puts("WIP !");
}

void load_config() {
	const char token[] = " \n";

	DataFile data_file = init_data_file(".config");

	char* config = read_string_from_file(data_file);

	char* key = strtok(config, token);
	char* value = strtok(NULL, token);

	int i = 0;
	while (key != NULL && value != NULL) {
		printf("%s => %s\n", key, value);
		// TODO asign the values somewhere
		if (value == NULL) {
			puts(
					"Le fichier de configuration n'est pas conforme, utilisation du fichier par défaut.");
			return;
		}
		key = strtok(NULL, token);
		value = strtok(NULL, token);

		i += 1;
	}
}

int login() {
	char pass[PASSLEN];
	puts("What is the password ?");
	if (get_secure_input(pass, sizeof(pass))) {
		//
	} else {
		return 0;
	}

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

void get_input(char* buffer, int* action) {
	while (1) { //While the input is not correct
		//printf("<%s>", buffer);
		if (fgets(buffer, sizeof(buffer) - 1, stdin)) {
			strtok(buffer, "\n");

			if (buffer[1] != '\0') { //If the input's length is > to 255 it will stay in the buffer
				//puts("Overflow");
				purge_buffer();
			}

			//printf("<%s>", buffer);
			if (sscanf(buffer, "%d", action) == 1) {
				break; //The input is correct
			} else {
				puts("Erreur, il ne faut entrer qu'un seul chiffre.");
			}
		}
	}
}

