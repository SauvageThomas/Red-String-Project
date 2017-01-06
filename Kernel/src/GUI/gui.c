/*
 * gui.c
 *
 *  Created on: 6 janv. 2017
 *      Author: Thomas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_gui() {

	int action;
	char buffer[2];

	puts("Bienvenue sur le moteur de recherche !");

	while (action != 0) {
		puts("1 - Demarrer une recherche");
		puts("2 - Se connecter en tant qu'administrateur");
		puts("3 - Voir les fichiers présents dans la base de données");
		puts("4 - ????????????????");
		puts("0 - Quitter");

		if (fgets(buffer, sizeof(buffer), stdin)) {
			if (sscanf(buffer, "%d", &action) == 1) {
			} else {
				input_error(buffer);
			}

		}

		purge_buffer();
		printf("<%s>\n", buffer);

		//strtok(buffer, "\n");
		printf("<%d>\n", action);
		switch (action) {
		case 0:
			exit(EXIT_SUCCESS);
		case 1:
			launch_search_engine();
			break;
		case 2:
			wip();
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

void wip() {
	puts("WIP !");
}

void input_error(char *input) {
	printf("\"%s\" n'existe pas. Veuillez reessayer.\n", input);
}

void purge_buffer() {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}
