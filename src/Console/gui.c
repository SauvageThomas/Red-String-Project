/*
 ============================================================================
 Name        : main.c
 Author      : Thomas
 Description : Console View of the software
 ============================================================================
 */

#include "gui.h"

void start_gui() {
	/*
	* Affiche le menu principal du logiciel et permet
	* différents choix pour l'utilisateur
	*/

	if (!DEBUG) {
		clear_console();
	}

	char buffer[2] = { ' ', '\0' };
	int admin = 0;

	Config config = load_config();

	while (buffer[0] != '0') {
		puts(
				" ================================================================");
		if (admin)
			puts(
					" |     *         *      MAIN  MENU (ADMIN)      *         *     |");
		else
			puts(
					" |     *         *          MAIN  MENU          *         *     |");
		puts(
				" ================================================================");
		puts(
				" |  1 - Run the Search Engine                                   |");
		puts(
				" |  2 - Show data base files                                    |");

		if (!admin) {
			puts(
					" |  3 - Connect as admin                                        |");
		} else {
			puts(
					" |  3 - Setup the configuration                                 |");
			puts(
					" |  4 - Change password                                         |");
			puts(
					" |  5 - Index all files                                         |");

		}
		puts(
				" |--------------------------------------------------------------|");
		puts(
				" |  0 - Quit                                                    |");
		puts(
				" ================================================================");


		// Recupère le choix de l'utilsateur et appelle la fonction associée
		get_input(buffer);

		switch (buffer[0]) {
		case '0':
			break;
		case '1':
			update_descriptors(config);
			search_gui(config);
			break;
		case '2':
			display_data_base(get_value_of(config, "path"));
			break;
		case '3':
			(admin == 0) ? admin = login() : config_gui();
			break;
		case '4':
			(admin == 0) ? input_error(buffer) : change_password();
			break;
		case '5':
			(admin == 0) ? input_error(buffer) : generate_all_descriptors(config);
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

void search_gui(Config config) {
	/*
	* Affiche le menu de recherche du moteur
	*/

	char buffer[2] = { ' ', '\0' };

	while (buffer[0] != '0') {
		puts(
				"\n ================================================================");
		puts(
				" |     *         *       SEARCH SELECTION       *         *     |");
		puts(
				" ================================================================");
		puts(
				" |  1 - With key-word                                           |");
		puts(
				" |  2 - With another file                                       |");
		puts(
				" |--------------------------------------------------------------|");
		puts(
				" |  0 - Back                                                    |");
		puts(
				" ================================================================");

		// Recupère le choix de l'utilsateur et appelle la fonction associée
		get_input(buffer);

		switch (buffer[0]) {
		case '0':
			break;
		case '1':
			search_by_keyword(get_value_of(config, "descriptors"));
			break;
		case '2':
			search_by_file(config);
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

void config_gui() {
	/*
	* Affiche le menu de configuration du moteur
	*/


	char buffer[2] = { ' ', '\0' };

	while (buffer[0] != '0') {
		puts(
				"\n ================================================================");
		puts(
				" |     *         *        CONFIG MANAGER        *         *     |");
		puts(
				" ================================================================");
		puts(
				" |  1 - Change the configuration                                |");
		puts(
				" |  2 - Reset the configuration                                 |");
		puts(
				" |--------------------------------------------------------------|");
		puts(
				" |  0 - Back                                                    |");
		puts(
				" ================================================================");


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

