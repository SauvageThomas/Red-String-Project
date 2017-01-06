/*
 ============================================================================
 Name        : main.c
 Author      : Thomas
 Version     :
 Description : Launches the search engine
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Include all data
#include "Data/constant.h"

// Include tests files
#include "Test/test.h"
#include "Test/minunit.h"

#include "Tools/data_handler.h"
#include "search_engine.h"
#include "GUI/gui.h"

/*
 * Description	: This is the only main which will be used in this project
 * Parameters	: None
 * Returns		: EXIT_SUCCES or EXIT_FAILURE
 */
int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);

	if (DEBUG) {
		puts("Debug is ON");
	}
	if (!PROD) {
		puts("Prod is OFF");
	} else {
		puts("Prod is ON");
		// exemple of path : ../res/FICHIER_PROJET/Textes/03-Des_chercheurs_parviennent_à_régénérer.xml
	}

	start_gui();

	//launch test
	if (TEST) {
		puts("Running tests ...\n");
		run_all_tests();
		puts("test done");
	}

	return EXIT_SUCCESS;
}
