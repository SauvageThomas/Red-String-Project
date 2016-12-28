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

/*
 * Description	: This is the only main which will be used in this project
 * Parameters	: None
 * Returns		: EXIT_SUCCES or EXIT_FAILURE
 */
int main(void) {

	//launch test
	if (TEST){
		puts("Running tests ...\n");
		run_all_tests();
		puts("test done");
	}

	if (DEBUG) {
		puts("Debug is ON");
	}
	if (!PROD) {
		puts("Prod is OFF");
	}
	else {
		puts("Prod is ON");
		launch_search_engine();
		// exemple of path : ../res/FICHIER_PROJET/Textes/03-Des_chercheurs_parviennent_à_régénérer.xml
	}

	return EXIT_SUCCESS;
}
