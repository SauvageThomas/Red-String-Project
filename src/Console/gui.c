/*
 ============================================================================
 Name        : main.c
 Author      : Thomas
 Description : Console View of the software
 ============================================================================
 */

#include "gui.h"

void display_rank(char *file_name, int rank){
	printf("[%d] %s\n", rank, file_name);
}


int login_view(){
	char pass[KPASSLEN];
	puts("Please, enter the password :");
	if (!get_secure_input(pass, sizeof(pass))) {
		puts("Input error");
		return 0;
	}
	else{
		int res = login(pass);
		if (res == -1){
			puts("The password file has not been detected. Password has been reset.");
			return 0;
		}

		else if (res == 0)
			puts("Wrong password : access forbidden !");
		else if (res == 1)
			puts("You are now connected as admin !");
		return res;
	}
}

void display_data_base() {
	/*
	Display every file with the good extension in the databse path
	*/
	DataFile* text_files = get_text_files();
	DataFile* image_files = get_image_files();
	DataFile* sound_files = get_sound_files();
	char* path = get_value_of("path");

	printf("Text Files :\n");
	for (int i = 0; i < get_nb_text(); i += 1) {
		printf("\t-%s\n", remove_path(text_files[i].path));
	}

	printf("\nImage Files :\n");
	for (int i = 0; i < get_nb_image(); i += 1) {
		printf("\t-%s\n", remove_path(image_files[i].path));
	}

	printf("\nAudio Files :\n");
	for (int i = 0; i < get_nb_sound(); i += 1) {
		printf("\t-%s\n", remove_path(sound_files[i].path));
	}
}

size_t get_sizet_from_config(char* key){
	char* size_str = get_value_of(key);
	if (size_str == NULL) {
		error_config_file();
	}
	return (size_t) strtol(size_str, (char **) NULL, 10);
}

void update_text_descriptor_wrp(int force){
	puts("\n\n ==================================================================");
	puts(" >>>    TEXT DESCRIPTOR UPDATE\n");
	printf(" -> Updating text descriptor...");
	int res_txt = update_text_descriptor(force);
	if (res_txt == 0)
		printf("\n -> %d text descriptors already up-to-date !\n", get_nb_text());
	else if (res_txt >= 1)
		printf(" Done !\n -> %d text descriptors updated !\n", get_nb_text());
	if (res_txt == 2)
		puts(" -> Index updated !");
}

void update_image_descriptor_wrp(int force){
	puts("\n\n ==================================================================");
	puts(" >>>    IMAGE DESCRIPTOR UPDATE\n");
	printf(" -> Updating image descriptor...");
	int res_image = update_image_descriptor(force);
	if (res_image == 0)
		printf("\n -> %d image descriptors already up-to-date !\n", get_nb_image());
	else if (res_image == 1)
		printf(" Done !\n -> %d image descriptors updated !\n", get_nb_image());
}

void update_sound_descriptor_wrp(int force){
	puts("\n\n ==================================================================");
	puts(" >>>    SOUND DESCRIPTOR UPDATE\n");
	printf(" -> Updating sound descriptor...");
	int res_sound = update_sound_descriptor(force);
	if (res_sound == 0)
		printf("\n -> %d sound descriptors already up-to-date !\n", get_nb_sound());
	else if (res_sound == 1)
		printf(" Done !\n -> %d sound descriptors updated !\n", get_nb_sound());
}

void init_search_engine(){
	puts("\n\n ==================================================================");
	puts(" >>>    SEARCH ENGINE : INITITIALIZATION\n");
	printf(" -> Loading data base...");
	load_data_base(get_value_of("path"));
	printf(" Done !\n");
	printf(" -> %d text file found !\n", get_nb_text());
	printf(" -> %d image file found !\n", get_nb_image());
	printf(" -> %d sound file found !\n", get_nb_sound());
}

void run_search_engine(int force){
	chrono();
	update_text_descriptor_wrp(force);
	update_image_descriptor_wrp(force);
	update_sound_descriptor_wrp(force);

	if(!DEBUG)
		clear_console();

	printf("\n >>>    GENERATING DESCRIPTORS TIME : %ds\n", chrono());
	puts(" >>>    SEARCH ENGINE : READY\n");
}

void show_main_menu() {
	/*
	* Affiche le menu principal du logiciel et permet
	* différents choix pour l'utilisateur
	*/

	if (DEBUG) {
		puts("DEBUG MODE : ACTIVATED");
	}
	else
		clear_console();

	char buffer[2] = { ' ', '\0' };
	int admin = 0;

	load_config();
	init_search_engine();

	while (buffer[0] != '0') {
		puts(" ================================================================");
		if (admin)
			puts(" |     *         *      MAIN  MENU (ADMIN)      *         *     |");
		else
			puts(" |     *         *       MAIN MENU (USER)       *         *     |");
		puts(" ================================================================");
		puts(" |  1 - Run the Search Engine                                   |");
		puts(" |  2 - Show data base files                                    |");

		if (!admin) {
			puts(" |  3 - Connect as admin                                        |");
		} 
		else {
			puts(" |  3 - Setup the configuration                                 |");
			puts(" |  4 - Change password                                         |");
			puts(" |  5 - Index all files                                         |");
		}
		puts(" |--------------------------------------------------------------|");
		puts(" |  0 - Quit                                                    |");
		puts(" ================================================================");


		// Recupère le choix de l'utilsateur et appelle la fonction associée
		get_input(buffer);

		switch (buffer[0]) {
		case '0':
			free_data_base();
			break;
		case '1':
			run_search_engine(0);
			show_search_menu();
			break;
		case '2':
			display_data_base();
			break;
		case '3':
			(admin == 0) ? admin = login_view() : show_config_menu();
			break;
		case '4':
			(admin == 0) ? input_error(buffer) : change_password();
			break;
		case '5':
			(admin == 0) ? input_error(buffer) : run_search_engine(1);
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

search_by_file_view(){
	/*
	* Lance la recherche par un fichier, quel que soit son format
	*/
	char* file_name = malloc(KSIZE);
	char* file_path = malloc(KSIZE * 2);

	strcpy(file_path, get_value_of("path"));

	puts("Please, enter a file path : ");
	if (get_secure_input(file_name, KSIZE)) {
		strcat(file_path, file_name);
		int res = search_data(file_path);
		// affiche le resultat de la recherche
		show_search_report(res);
	}
}

void show_search_menu() {
	/*
	* Affiche le menu de recherche du moteur
	*/

	char buffer[2] = { ' ', '\0' };

	while (buffer[0] != '0') {
		puts("\n ================================================================");
		puts(" |     *         *       SEARCH SELECTION       *         *     |");
		puts(" ================================================================");
		puts(" |  1 - With key-word                                           |");
		puts(" |  2 - With another file                                       |");
		puts(" |--------------------------------------------------------------|");
		puts(" |  0 - Back                                                    |");
		puts(" ================================================================");

		// Recupère le choix de l'utilsateur et appelle la fonction associée
		get_input(buffer);

		switch (buffer[0]) {
		case '0':
			break;
		case '1':
			search_by_keyword(get_value_of("descriptors"));
			break;
		case '2':
			search_by_file_view();
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

void show_config_menu() {
	/*
	* Affiche le menu de configuration du moteur
	*/


	char buffer[2] = { ' ', '\0' };

	while (buffer[0] != '0') {
		puts("\n ================================================================");
		puts(" |     *         *        CONFIG MANAGER        *         *     |");
		puts(" ================================================================");
		puts(" |  1 - Change the configuration                                |");
		puts(" |  2 - Reset the configuration                                 |");
		puts(" |--------------------------------------------------------------|");
		puts(" |  0 - Back                                                    |");
		puts(" ================================================================");


		// Recupère le choix de l'utilsateur et appelle la fonction associée
		get_input(buffer);

		switch (buffer[0]) {
		case '0':
			break;
		case '1':
			modif_config();
			break;
		case '2':
			reset_config();
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

