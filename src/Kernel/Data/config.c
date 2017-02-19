
#include "config.h"

typedef struct {
	char** config;
	size_t size;
	size_t size_word;
} Config;


Config CONFIG = {NULL, -1, -1};

void error_config_file() {
	/*
	* Reset de la config si elle n'est pas lisible par le programme
	*/
	reset_config();
	puts("Error in the config file. It has been replaced by the backup file.");
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


void init_config(){
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

	CONFIG.size = 0;
	CONFIG.size_word = KSIZEWORD;

	CONFIG.config = malloc(sizeof(char*) * i * 2);
	if (CONFIG.config == NULL) {
		fprintf(stderr, "Malloc in load config failed %s\n", strerror(errno));
	}

	for (int j = 0; j < i; j += 1) {
		CONFIG.config[i] = malloc(KSIZEWORD);
		if (CONFIG.config[i] == NULL) {
			fprintf(stderr, "Malloc in loop of load config failed %s\n", strerror(errno));
		}
	}
	char* key = strtok(config, token);
	char* value = strtok(NULL, token);

	while (key != NULL && value != NULL) {
		CONFIG.config[CONFIG.size] = key;
		CONFIG.config[CONFIG.size + 1] = value;

		if (value == NULL) {
			puts("Corrupted config file, default one used.");
			//TODO: faire un fichier par d�faut et le charger � la place de NULL
			return CONFIG;
		}
		key = strtok(NULL, token);
		value = strtok(NULL, token);

		CONFIG.size += 2;
	}
}


void load_config() {
	/*
	Read the config file and load it into the Config structure
	If the file doesn't exist it calls the error_config_file function
	*/

	if (CONFIG.size == -1){
		init_config();
	}
}

size_t get_sizet_from_config(char* key){
	char* size_str = get_data_from_config(key);
	if (size_str == NULL) {
		error_config_file();
	}
	return (size_t) strtol(size_str, (char **) NULL, 10);
}

char* get_data_from_config(const char* value) {
	/*
	Return the value associated to the key input
	If it doesn't contain it, it calls error_config_file 
	*/
	load_config();
	for (int i = 0; i < CONFIG.size; i += 2) {
		if (!strcmp(CONFIG.config[i], value)) {
			return CONFIG.config[i + 1];
		}
	}
	error_config_file();
	return get_data_from_config(value);
}