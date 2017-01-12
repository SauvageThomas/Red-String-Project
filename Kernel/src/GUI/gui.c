/*
 * gui.c
 *
 *  Created on: 6 janv. 2017
 *      Author: Thomas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gui.h"
#include "functions.h"
#include "../search_engine.h"
#include "../Data/constant.h"

void start_gui() {
	if (!DEBUG){
		clear_console();
	}
	
	int action = 1; 
	char buffer[2];
	int admin = 0;

	Config config = load_config();

	while (action != 0) {
		//clear_console();
		puts(" ================================================================");
		if (admin)
			puts(" |     *         *      MAIN  MENU (ADMIN)      *         *     |");
		else
			puts(" |     *         *          MAIN  MENU          *         *     |");
		puts(" ================================================================");
		puts(" |  1 - Run the Search Engine                                   |"); 
		puts(" |  2 - Show data base files                                    |");

		if (!admin) {
			puts(" |  3 - Connect as admin                                        |");
		} else {
			puts(" |  3 - Setup the configuration                                 |");
			puts(" |  4 - Show performances stats                                 |");
			puts(" |  5 - Change password                                         |");
		}
		puts(" |--------------------------------------------------------------|");
		puts(" |  0 - Quit                                                    |");
		puts(" ================================================================");

		get_input(buffer, &action);

		//clear_console();

		switch (action) {
			case 0:
				close_search_engine();
				break;
			case 1:
				launch_search_engine(config);
				break;
			case 2:
				wip();
				break;
			case 3:
				(admin == 0) ? admin = login() : config_gui();
				break;
			case 4:
				(admin == 0) ? input_error(buffer) : wip();
				break;
			case 5:
				(admin == 0) ? input_error(buffer) : wip();
				break;
			default:
				input_error(buffer);
				break;
		}
	}
}

void search_gui(Config config) {
	int action;
	char buffer[2];

	while (action != 0) {
		puts("\n ================================================================");
		puts(" =     *         *       SEARCH SELECTION       *         *     =");
		puts(" ================================================================");
		puts(" |  1 - with key-word                                           |");
		puts(" |  2 - with another file                                       |");
		puts(" |--------------------------------------------------------------|");
		puts(" |  0 - Retour                                                  |");
		puts(" ================================================================");
		
		get_input(buffer, &action);

		switch (action) {
		case 0:
			break;
		case 1:
			search_by_keyword();
			break;
		case 2:
			search_by_file(get_value_of(config, "path"));
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

void config_gui() {

	int action;
	char buffer[2];
 	
	while (action != 0) {
		puts("\n ================================================================");
		puts(" =     *         *        CONFIG MANAGER        *         *     =");
		puts(" ================================================================");
		puts(" |  1 - Modifier le fichier de configuration                    |");
		puts(" |  2 - Remettre les parametres initiaux                        |");
		puts(" |--------------------------------------------------------------|");
		puts(" |  0 - Retour                                                  |");
		puts(" ================================================================");

		get_input(buffer, &action);

		switch (action) {
		case 0:
			break;
		case 1:
			modif_config();
			break;
		case 2:
			wip();
			break;
		default:
			input_error(buffer);
			break;
		}
	}
}

