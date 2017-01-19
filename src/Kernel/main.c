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
#include "../Console/gui.h"

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
	puts("\n\n");


	//launch test
	if (TEST) {
		run_all_tests();
		return EXIT_SUCCESS;
	}

	
	if (DEBUG) puts("DEBUG MODE : ACTIVATED");

	if (PROD) start_gui();

	return EXIT_SUCCESS;
}
