/*
 ============================================================================
 Name        : functions.c
 Author      : Thomas
 Description : Controller of the software
 ============================================================================
 */

#include <jni.h>
#include "functions.h"
#include "../../jni/src_Controller_controller.h"

const int pass_key[] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215, 48421,
		629, 314, 4784, 5102, 914, 213, 316, 145, 78 };

void search_by_file(Config config) {
	/*
	* Lance la recherche par un fichier, quel que soit son format
	*/

	char* tmp = get_value_of(config, "path");

	char* file_name = malloc(KSIZE);
	char* file_path = malloc(KSIZE * 2);

	strcpy(file_path, tmp);

	puts("Please, enter a file path : ");
	if (get_secure_input(file_name, KSIZE)) {
		strcat(file_path, file_name);
		int res = search_data(config, file_path);
		// affiche le resultat de la recherche
		show_search_report(res);
	}
}

void update_descriptors(Config config) {
	/*
	 * UPDATE DESCRIPTORS AND INDEX IF NEEDED
	 */

	puts("\n\n ==================================================================");
	puts(" >>>    SEARCH ENGINE : INITITIALIZATION");
	puts("-> checking descriptors...");
	char *path = get_value_of(config, "descriptors");
	chrono();
	Directory dir = get_all_files(get_value_of(config, "path"));


	// Text descriptor update
	check_text_descriptor(path, dir);


	// Image descriptor update
	char *quant = get_value_of(config, "quantification");
	if (quant == NULL) {
		error_config_file();
	}
	size_t n = (size_t) strtol(quant, (char **) NULL, 10);
	check_image_descriptor(path, dir, n);


	// Sound descriptor update
	char *size_window = get_value_of(config, "taille_des_fenetres");
	char *nb_intervalles = get_value_of(config, "nombre_de_barre");
	if (size_window == NULL || nb_intervalles == NULL) {
		error_config_file();
	}
	size_t k = (size_t) strtol(size_window, (char **) NULL, 10);
	size_t m = (size_t) strtol(nb_intervalles, (char **) NULL, 10);
	check_sound_descriptor(path, dir, k, m);


	if(!DEBUG)
		clear_console();

	printf("\n >>>    GENERATING DESCRIPTORS TIME : %ds\n", chrono());
	puts(" >>>    SEARCH ENGINE : READY\n");
}

void error_config_file() {
	/*
	* Reset de la config si elle n'est pas lisible par le programme
	*/
	reset_config();
	puts("Error in the config file. It has been replaced by the backup file.");
}

void search_by_keyword(char *path) {
	/*
	Allow the user to search a file using a keyword
	*/
	puts("Please, enter a unique key word : ");

	char *keyword = malloc(KSIZEWORD);
	get_secure_input(keyword, KSIZE);

	char* file_path = malloc(KSIZE * 2);
	strcpy(file_path, path);

	strcat(file_path, "text_index");

	DataFile df = init_data_file(file_path);

	char *content = read_string_from_file(df);

	int length = strlen(content);
	int found = 0;
	int cpt = 0;
	puts("Result :");
	for (int i = 0; i < length; i += 1) {
		if (content[i] == '>') {
			char *tmp = malloc(KSIZEWORD);
			i += 1;
			sscanf(&content[i], "%s", tmp);
			//printf("<%s> <%s>\n", tmp, keyword);
			if (!strcmp(tmp, keyword)) {

				//puts("Ok");
				found = 1;
				i += strlen(keyword) + 1;
			}
		} else if (found) {
			char *final_string = malloc(KSIZEWORD * 45);
			while (content[i] != '>') {

				if (content[i] == '\n') {
					if (cpt > 5) {
						break;
					}
					final_string = pretty_print_string(final_string);
					printf("%s\n", final_string);
					strcpy(final_string, "");
					cpt += 1;
				}
				//putchar(content[i]);
				strncat(final_string, &content[i], 1);
				i += 1;

			}
			break;
			exit(0);
		}
	}
	if (!found) {
		puts("No result found");
	}
}

void modif_config() {
	/*
	Use the default application to open the config file
	and modify it
	*/
	if (OS == 1) {
		system(".config");
	} else {
		system("xdg-open .config");
	}
}

void generate_all_descriptors(Config config) {
	/*
	* Genere tous les descripteurs
	*/

	char *path = get_value_of(config, "descriptors");

	// charge l'ensemble des fichiers de la base de donnée
	Directory dir = get_all_files(get_value_of(config, "path"));

	char *full_path[KSIZE*2];

	// descripteur de texte
	strcpy(full_path, path);
	strcat(full_path, "text_descriptors");
	DataFile df = init_data_file(full_path);
	generate_text_descriptors(df, dir);

	// descripteur image
	char *quant = get_value_of(config, "quantification");
	size_t n = (size_t) strtol(quant, (char **) NULL, 10);
	strcpy(full_path, path);
	strcat(full_path, "image_descriptors");
	df = init_data_file(full_path);
	generate_image_descriptors(df, dir, n);

	// descripteur son
	char *size_window = get_value_of(config, "taille_des_fenetres");
	size_t k = (size_t) strtol(size_window, (char **) NULL, 10);
	char *nb_intervalles = get_value_of(config, "nombre_de_barre");
	size_t m = (size_t) strtol(nb_intervalles, (char **) NULL, 10);
	strcpy(full_path, path);
	strcat(full_path, "sound_descriptors");
	df = init_data_file(full_path);
	generate_sound_descriptors(df, dir, k, m);
}

void reset_config() {
	/*
	Recreate the config file with the backup file.
	If the backup file doesn't exist, the programm with an error
	*/
	DataFile data_file = init_data_file(".backup");

	if (data_file.length == 0) {
		puts("Major error, no backup file. Quitting ...");
		exit(1);
	}

	char* config = read_string_from_file(data_file);
	data_file = init_data_file(".config");
	write_string_in_file(data_file, config);
}

Config load_config() {
	/*
	Read the config file and load it into the Config structure
	If the file doesn't exist it calls the error_config_file function
	*/
	char token[] = " \n";

	DataFile data_file = init_data_file(".config");
	if (data_file.length == 0) {
		reset_config();
	}

	char* config = read_string_from_file(data_file);
	char* tmp = config;

	int i = 0;
	//Count number of occurence of '\n' in string
	for (i = 0; tmp[i]; tmp[i] == '\n' ? i++ : *tmp++)
		;
	i = (i + 1) * 2;

	Config configuration;
	configuration.size = 0;
	configuration.size_word = KSIZEWORD;

	configuration.config = malloc(sizeof(char*) * i * 2);
	if (configuration.config == NULL) {
		fprintf(stderr, "Malloc in load config failed %s\n", strerror(errno));
	}

	for (int j = 0; j < i; j += 1) {
		configuration.config[i] = malloc(KSIZEWORD);
		if (configuration.config[i] == NULL) {
			fprintf(stderr, "Malloc in loop of load config failed %s\n",
					strerror(errno));
		}
	}
	char* key = strtok(config, token);
	char* value = strtok(NULL, token);

	while (key != NULL && value != NULL) {
		configuration.config[configuration.size] = key;
		configuration.config[configuration.size + 1] = value;

		if (value == NULL) {
			puts("Corrupted config file, default one used.");
			//TODO: faire un fichier par d�faut et le charger � la place de NULL
			return configuration;
		}
		key = strtok(NULL, token);
		value = strtok(NULL, token);

		configuration.size += 2;
	}
	puts("Configuration succesfully loaded !");
	return configuration;
}

void display_data_base(char *path) {
	/*
	Display every file with the good extension in the databse path
	*/
	Directory dir = get_all_files(path);

	printf("Text Files :\n");
	for (int i = 0; i < dir.txt_size; i += 1) {
		printf("\t-%s\n", remove_path(dir.txt_files[i].path));
	}

	printf("\nImage Files :\n");
	for (int i = 0; i < dir.image_size; i += 1) {
		printf("\t-%s\n", remove_path(dir.image_files[i].path));
	}

	printf("\nAudio Files :\n");
	for (int i = 0; i < dir.audio_size; i += 1) {
		printf("\t-%s\n", remove_path(dir.audio_files[i].path));
	}
}

char *remove_path(char *in) {
	/*
	Internal function used to remove the path of file Ex: /bin/bash => bash
	*/
	char *out = malloc(KSIZE);
	out[0] = '\0';

	char c = in[0];
	int j = 0;
	while (c != '\0') {
		c = in[j];
		strncat(out, &c, 1);
		if (c == '/') {
			out[0] = '\0';
		}
		j += 1;
	}
	return out;
}

char* get_value_of(Config config, const char* value) {
	/*
	Return the value associated to the key input
	If it doesn't contain it, it calls error_config_file 
	*/
	for (int i = 0; i < config.size; i += 2) {
		if (!strcmp(config.config[i], value)) {
			return config.config[i + 1];
		}
	}
	error_config_file();
	return get_value_of(config, value);
}

void change_password() {
	/*
	Allow an admin to change his password
	*/
	char pass[KPASSLEN];
	puts("Please, enter the password :");
	get_secure_input(pass, sizeof(pass));

	DataFile data_file = init_data_file(".pass");

	xor_crypt(pass);
	write_string_in_file(data_file, pass);
	puts("Password correctly changed !");
}

int login() {
	/*
	Allow a user to connect as an admin
	*/
	char pass[KPASSLEN];
	puts("Please, enter the password :");
	if (!get_secure_input(pass, sizeof(pass))) {
		return 0;
	}

	DataFile data_file = init_data_file(".pass");

	if (data_file.length == 0) { //The file is empty or does not exist
		strcpy(pass, "admin");
		xor_crypt(pass);
		write_string_in_file(data_file, pass);
		puts(
				"The password file has not been detected. Password has been reset.");
		return 0;
	}

	char* compare = read_string_from_file(data_file);

	xor_crypt(compare);

	if (!strcmp(compare, pass)) {
		puts("You are now connected as admin !");
		return 1;
	} else {
		puts("Wrong password : access forbidden !");
		return 0;
	}

}

void wip() {
	/*
	Internal function
	*/
	puts("Work in progress : not yet implemented !");
}

void input_error(char *input) {
	/*
	Display an error
	*/
	printf("command not found : %s ! Please, try again.\n", input);
}

void xor_crypt(char *password) {
	/*
	Crypt an input (modify the input)
	*/
	for (int i = 0; i < KPASSLEN; i += 1) {
		password[i] ^= pass_key[i];
	}
}

void get_input(char* buffer) {
	/*
	Get the input for the menu, only 1 digit
	*/
	while (get_secure_input(buffer, 2) != 1) {
		puts("1 digit was expected, please try again !");
	}
}

void clear_console() {
	/*
	Clear the console
	*/
	printf("\033[H\033[J\n");
}

time_t chrono() {
	/*
	The first call create the chrono (you should not use the outpout)
	and the second call return the time between the first and the second call
	*/
	static time_t prev_time;
	time_t res = time(NULL) - prev_time;
	prev_time = time(NULL);
	return res;
}
