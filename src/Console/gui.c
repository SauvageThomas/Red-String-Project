/*
 ============================================================================
 Name        : main.c
 Author      : Thomas
 Description : Console View of the software
 ============================================================================
 */

#include "gui.h"

size_t get_sizet_from_config(char* key){
	char* size_str = get_value_of(key);
	if (size_str == NULL) {
		error_config_file();
	}
	return (size_t) strtol(size_str, (char **) NULL, 10);
}

void update_text_descriptor_wrp(char* path, Directory dir){
	puts("\n\n ==================================================================");
	puts(" >>>    TEXT DESCRIPTOR UPDATE\n");
	printf(" -> Updating text descriptor...");
	int res_txt = update_text_descriptor(path, dir);
	if (res_txt == 0)
		printf("\n -> %d text descriptors already up-to-date !\n", dir.txt_size);
	else if (res_txt >= 1)
		printf(" Done !\n -> %d text descriptors updated !\n", dir.txt_size);
	if (res_txt == 2)
		puts(" -> Index updated !");
}

void update_image_descriptor_wrp(char* path, Directory dir){
	puts("\n\n ==================================================================");
	puts(" >>>    IMAGE DESCRIPTOR UPDATE\n");
	printf(" -> Updating image descriptor...");
	size_t n = get_sizet_from_config("quantification");
	int res_image = update_image_descriptor(path, dir, n);
	if (res_image == 0)
		printf("\n -> %d image descriptors already up-to-date !\n", dir.image_size);
	else if (res_image == 1)
		printf(" Done !\n -> %d image descriptors updated !\n", dir.image_size);
}

void update_sound_descriptor_wrp(char* path, Directory dir){
	puts("\n\n ==================================================================");
	puts(" >>>    SOUND DESCRIPTOR UPDATE\n");
	printf(" -> Updating sound descriptor...");
	size_t k = get_sizet_from_config("taille_des_fenetres");
	size_t m = get_sizet_from_config("nombre_de_barre");
	int res_sound = update_sound_descriptor(path, dir, k, m);
	if (res_sound == 0)
		printf("\n -> %d sound descriptors already up-to-date !\n", dir.audio_size);
	else if (res_sound == 1)
		printf(" Done !\n -> %d sound descriptors updated !\n", dir.audio_size);
}

Directory init_search_engine(){
	puts("\n\n ==================================================================");
	puts(" >>>    SEARCH ENGINE : INITITIALIZATION\n");
	printf(" -> Loading data base...");
	
	Directory dir = get_all_files(get_value_of("path"));
	printf(" Done !\n");
	printf(" -> %d text file found !\n", dir.txt_size);
	printf(" -> %d image file found !\n", dir.image_size);
	printf(" -> %d sound file found !\n", dir.audio_size);
	return dir;
}

void run_search_engine(){
	
	Directory dir = init_search_engine();
	char *path = get_value_of("descriptors");
	chrono();
	update_text_descriptor_wrp(path, dir);
	update_image_descriptor_wrp(path, dir);
	update_sound_descriptor_wrp(path, dir);

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
			break;
		case '1':
			run_search_engine();
			show_search_menu();
			break;
		case '2':
			display_data_base(get_value_of("path"));
			break;
		case '3':
			(admin == 0) ? admin = login() : show_config_menu();
			break;
		case '4':
			(admin == 0) ? input_error(buffer) : change_password();
			break;
		case '5':
			(admin == 0) ? input_error(buffer) : generate_all_descriptors();
			break;
		default:
			input_error(buffer);
			break;
		}
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
			search_by_file();
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

