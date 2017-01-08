/*
 * functions.c
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "functions.h"
#include "../Tools/report.h"
#include "../Tools/data_handler.h"
#include "../Search/data_manager.h"
#include "../Search/text_finder.h"
#include "../Search/image_finder.h"
#include "../Search/sound_finder.h"

const int pass_key[] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215, 48421,
		629, 314, 4784, 5102, 914, 213, 316, 145, 78 };

void search_by_file(char* path) {
	char file[SIZE]; //255 is the max size limit on most used file systems
	char file_path[SIZE * 2];
	strcpy(file_path, path);

	puts("Please, enter a file path : ");
	printf(">>");

	if (get_secure_input(file, sizeof(file))) {
		strcat(file_path, file);

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

Config load_config() {

	const char token[] = " \n";

	DataFile data_file = init_data_file(".config");

	char* config = read_string_from_file(data_file);
	char* tmp = config;

	int i = 0;
	//Count number of occurence of '\n' in string
	for (i = 0; tmp[i]; tmp[i] == '\n' ? i++ : *tmp++)
		;
	i = (i + 1) * 2;

	Config configuration;
	char** config_array = malloc(i);
	for (int i = 0; i < i; i += 1) {
		config_array[i] = malloc(SIZEMOT);
	}
	configuration.config = config_array;
	configuration.size = 0;
	configuration.size_word = SIZEMOT;

	char* key = strtok(config, token);
	char* value = strtok(NULL, token);

	while (key != NULL && value != NULL) {
		printf("%s => %s\n", key, value);

		config_array[configuration.size] = key;
		config_array[configuration.size + 1] = value;

		if (value == NULL) {
			puts(
					"Le fichier de configuration n'est pas conforme, utilisation du fichier par d�faut.");
			//TODO faire un fichier pa d�faut et le charger � la place de NULL
			return configuration;
		}
		key = strtok(NULL, token);
		value = strtok(NULL, token);

		configuration.size += 2;
	}
	return configuration;
}

char* get_value_of(Config config, const char* value) {
	for (int i = 0; i < config.size; i += 2) {
		if (!strcmp(config.config[i], value)) {
			return config.config[i + 1];
		}
	}
	return NULL;
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
		puts("Vous �tes identifi� en tant qu'admin !");
		return 1;
	} else {
		puts("Identification refus�e.");
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
		password[i] ^= pass_key[i];
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

