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
#include "Tools/hash_map.h"
#include "search_engine.h"
#include "GUI/gui.h"

/*
 * Description	: This is the only main which will be used in this project
 * Parameters	: None
 * Returns		: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void) {
	
	// Resolve error for windows execution
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);

	if (DEBUG) {
		puts("DEBUG : ON");
	}
	if (!PROD) {
		puts("PROD  : OFF");
	} else {
		puts("PROD  : ON");
		// exemple of path : 03-Des_chercheurs_parviennent_à_régénérer.xml
	}

	if (PROD){
		start_gui();
	}

	//launch test
	if (TEST) {
		run_all_tests();
	}

	return EXIT_SUCCESS;
}
