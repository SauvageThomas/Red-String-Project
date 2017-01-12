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
#include "../Data/constant.h"
#include "../Tools/report.h"
#include "../Tools/data_handler.h"
#include "../Search/data_manager.h"
#include "../Search/text_finder.h"
#include "../Search/image_finder.h"
#include "../Search/sound_finder.h"

const int pass_key[] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215, 48421, 629, 314, 4784, 5102, 914, 213, 316, 145, 78 };

void search_by_file(Config config) {
	char* file_name = malloc(KSIZE);
	char* file_path = malloc(KSIZE * 2);
	strcpy(file_path, get_value_of(config, "path"));
	puts("Please, enter a file path : ");
	if (get_secure_input(file_name, KSIZE)) {
		strcat(file_path, file_name);
		int res = search_data(config, file_path);
		show_search_report(res);
	}
}

void search_by_keyword() {
	wip();
}

void modif_config() {
	/*
	char* str = "!!";
	DataFile data_file = init_data_file(".config");
	*/
	wip();
}

Config load_config() {

	const char token[] = " \n";

	DataFile data_file = init_data_file(".config");
	if(data_file.length==0){
		//TODO: Create the file according to the backup file
	}

	char* config = read_string_from_file(data_file);
	char* tmp = config;

	int i = 0;
	//Count number of occurence of '\n' in string
	for (i = 0; tmp[i]; tmp[i] == '\n' ? i++ : *tmp++)
		;
	i = (i + 1) * 2;

	Config configuration;
	char** config_array = malloc(sizeof(char*) * i);
	for (int j = 0; j < i; j += 1) {
		config_array[i] = malloc(KSIZEWORD);
	}
	configuration.config = config_array;
	configuration.size = 0;
	configuration.size_word = KSIZEWORD;

	char* key = strtok(config, token);
	char* value = strtok(NULL, token);

	while (key != NULL && value != NULL) {
		config_array[configuration.size] = key;
		config_array[configuration.size + 1] = value;

		// DEAD CODE ???
		if (value == NULL) {
			puts(
					"Le fichier de configuration n'est pas conforme, utilisation du fichier par défaut.");
			//TODO: faire un fichier par défaut et le charger à la place de NULL
			return configuration;
		}
		key = strtok(NULL, token);
		value = strtok(NULL, token);

		configuration.size += 2;
	}
	puts("Configuration succesfully done !");
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

	char pass[KPASSLEN];
	puts("Please, enter the password :");
	if (!get_secure_input(pass, sizeof(pass))) {
		return 0;
	}

	DataFile data_file = init_data_file(".pass");

	printf("length %d\n", data_file.length);

	if (data_file.length == 0) { //The file is empty or does not exist
		strcpy(pass, "admin");
		xor_crypt(pass);
		write_string_in_file(data_file, pass);
		puts("Aucun mot de passe détecté, remise à zéro du fichier.");
		return 0;
	}

	char* compare = read_string_from_file(data_file);

	xor_crypt(compare);

	if (!strcmp(compare, pass)) {
		puts("You are now connected as admin !");
		return 1;
	} else {
		puts("wrong password : access forbidden !");
		return 0;
	} 

}

void wip() {
	puts("Work in progress : not yet implemented !");
}

void input_error(char *input) {
	printf("command not found : %s ! Please, try again.\n", input);
}

void xor_crypt(char *password) {
	for (int i = 0; i < KPASSLEN; i += 1) {
		password[i] ^= pass_key[i];
	}
}

void get_input(char* buffer, int* action) {
	while (1) { //TODO: pas beau
		printf(">> ");
		if (fgets(buffer, sizeof(buffer) - 1, stdin)) {
			strtok(buffer, "\n");

			if (buffer[1] != '\0') { //If the input's length is > to 255 it will stay in the buffer
				purge_buffer();
			}

			if (sscanf(buffer, "%d", action) == 1) {
				break; //The input is correct
			} else {
				puts("format error : 1 digit expected !");
			}
		}
	}
}

void clear_console(){
	printf("\033[H\033[J\n");
}
