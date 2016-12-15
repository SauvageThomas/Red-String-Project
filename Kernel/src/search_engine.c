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
}

void run_search_engine(){
	puts("SEARCH ENGINE : RUN");
	//scanf();
}
