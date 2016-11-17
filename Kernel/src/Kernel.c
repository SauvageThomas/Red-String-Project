/*
 ============================================================================
 Name        : Kernel.c
 Author      : Thomas
 Version     :
 Description : Launches the search engine
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "Data/constant.h"
#include "Test/test.h"

//This is the only main which will be used in this project
int main(void) {
	if (DEBUG) {
		puts("Debug is ON");
	}
	if (!PROD) {
		puts("Prod is OFF");
	}
	//launch test
	if(TEST){
		launch_all_test();
	}

	return EXIT_SUCCESS;
}
