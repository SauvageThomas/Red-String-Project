
#include "menus.h"

void show_main_menu() {
	/*
	* Affiche le menu principal du logiciel et permet
	* différents choix pour l'utilisateur
	*/

	char buffer[2] = { ' ', '\0' };
	int admin = 0;

	while (buffer[0] != '0') {
		puts(" ================================================================");
		if (admin)
			puts(" |     *         *      MAIN  MENU (ADMIN)      *         *     |");
		else
			puts(" |     *         *       MAIN MENU (USER)       *         *     |");
		puts(" ================================================================");
		puts(" |  1 - Research a file                                         |");
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
			(admin == 0) ? input_error(buffer) : update_descriptors(1);
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
			search_by_keywords_view();
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