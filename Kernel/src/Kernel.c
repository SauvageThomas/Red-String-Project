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

// Include all data
#include "Data/constant.h"

// Include tests files
#include "Test/test.h"
#include "Test/minunit.h"

#include "Tools/tools.h"

//This is the only main which will be used in this project
int main(void) {

	char src[50], dest[50];

	strcpy(src, "This is source");
	strcpy(dest, "This is destination");

	strcat(dest, src);

	printf("Final destination string : |%s|", dest);


	if (DEBUG) {
		puts("Debug is ON");
	}
	if (!PROD) {
		puts("Prod is OFF");
	}
	//launch test
	if (TEST) {
		puts("Running tests ...\n");
		run_all_tests();
		puts("test done");
	}

	return EXIT_SUCCESS;
}
