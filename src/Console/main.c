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
#include "../Kernel/Data/constant.h"

// Include tests files
#include "../Kernel/Test/test.h"
#include "../Console/gui.h"


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

	if (PROD) show_main_menu();

	return EXIT_SUCCESS;
}
