/*
 * functions.c
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "../Tools/report.h"
#include "../Tools/data_handler.h"
#include "../Search/data_manager.h"
#include "../Search/text_finder.h"
#include "../Search/image_finder.h"
#include "../Search/sound_finder.h"

void search_by_file() {
	char file[SIZE]; //255 is the max size limit on most used file systems
	char file_path[SIZE * 2];
	strcpy(file_path, "res/FICHIER_PROJET/Textes/");

	puts("Please, enter a file path : ");
	printf(">>");

	if (get_secure_input(file, sizeof(file))) {
		strcat(file_path, file);

		printf("%s", file_path);

		int res = search_data(file_path);
		show_search_report(res);
		if (!res) {
			DataFile data_file = init_data_file(file_path);
			switch (get_data_file_extension(data_file)) {
			case TEXT:
				find_text(data_file);
				break;
			case IMAGE:
				find_image(data_file);
				break;
			case SOUND:
				find_sound(data_file);
				break;
			default:
				break;
			}
		}
	} else {
		puts("error");
		//Handle the error ?
	}
}

void search_by_keyword() {

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


