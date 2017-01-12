/*
 ============================================================================
 Name        : search_engine.c
 Author      : Kévin
 Version     :
 Description : Search Engine
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "search_engine.h"
#include "Descriptor/descriptor_generator.h"
#include "Descriptor/index_generator.h"
#include "Search/data_manager.h"
#include "Tools/report.h"
#include "Tools/data_handler.h"
#include "GUI/gui.h"
#include "Data/constant.h"

void launch_search_engine(Config config) {

	/*
	 * MANAGE ALL THE SOFTWARE PROCESS
	 */

	puts("*   *   *   SEARCH ENGINE : LAUNCH");
	init_search_engine(config);
	run_search_engine(config);
	close_search_engine();
}

void init_search_engine(Config config) {

	/*
	 * UPDATE DESCRIPTORS AND INDEX IF NEEDED
	 */
	puts("------------------------------------------------------------------");
	puts("*   *   *   SEARCH ENGINE : INITITIALIZATION");
	//puts("-> checking descriptors...");
	int updated = check_descriptors(get_value_of(config, "descriptors"));
	if (updated == EXIT_SUCCESS){
		puts("Index is already up to date.");
	} else {
		puts("-> updating index...");
		update_index();
	}
}

void run_search_engine(Config config) {

	/*
	 * RUN THE RESEARCH
	 */

	puts("*   *   *   SEARCH ENGINE : RUN");
	search_gui(config);
}

void close_search_engine() {

	/*
	 * free resources if needed ?
	 */

	puts("*	   *   *   SEARCH ENGINE : CLOSE");
}
