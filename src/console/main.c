/*
 ============================================================================
 Name        : main.c
 Author      : Thomas
 Description : Launches the Tests or the Gui
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Include all data
#include "../kernel/data/constant.h"
#include "menus.h"

// Include tests files
#include "../kernel/test/test.h"


int main() {
	/*
	 * Description	: This is the only main which will be used in this project
	 * Parameters	: None
	 * Returns		: EXIT_SUCCESS or EXIT_FAILURE
	 */
	
	// Resolve error for windows execution
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	puts("\n\n");


	//launch test
	if (TEST) {
		run_all_tests();
		return EXIT_SUCCESS;
	}

	if (PROD) {
		if (DEBUG) {
			puts("DEBUG MODE : ACTIVATED");
		}
		else{
			clear_console();
		}
		load_config();
		init_search_engine();
		update_descriptors(0);
		show_main_menu();
	}

	return EXIT_SUCCESS;
}
