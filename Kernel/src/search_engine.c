/*
 ============================================================================
 Name        : search_engine.c
 Author      : Kévin
 Version     :
 Description : Search Engine
 ============================================================================
 */

#include <stdio.h>
#include "search_engine.h"

void launch_search_engine(){
	puts("SEARCH ENGINE : LAUNCH");
	init_search_engine();
	run_search_engine();
}

void init_search_engine(){
	puts("SEARCH ENGINE : INIT");
	puts("\t - check descriptors");
	puts("\t - check index");
}

void run_search_engine(){
	puts("SEARCH ENGINE : RUN");
	char file_path[100];
	puts("Please, enter a file path : ");
	scanf("%s", file_path);
	printf("file to treat : %s\n", file_path);
}
