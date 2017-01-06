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
#include "Descriptor/descriptor_generator.h"
#include "Descriptor/index_generator.h"
#include "Search/data_manager.h"
#include "Tools/report.h"

void launch_search_engine() {

	/*
	 * MANAGE ALL THE SOFTWARE PROCESS
	 */

	puts("SEARCH ENGINE : LAUNCH");
	init_search_engine();
	run_search_engine();
	close_search_engine();
}

void init_search_engine() {

	/*
	 * UPDATE DESCRIPTORS AND INDEX IF NEEDED
	 */

	puts("SEARCH ENGINE : INITITIALIZATION");
	puts("-> checking descriptors...");
	int updated = check_descriptors();
	if (updated) {
		puts("Index is already up to date.");
	} else {
		puts("-> updating index...");
		update_index();
	}
}

void run_search_engine() {

	/*
	 * RUN THE RESEARCH FROM A FILE PATH
	 */

	puts("SEARCH ENGINE : RUN");
	char file_path[200];
	puts("Please, enter a file path : ");

	if (fgets(file_path, sizeof(file_path), stdin)) {
		int res = search_data(file_path);
		show_search_report(res);
	}else{
		//Handle the error ?
	}
	//scanf("%s", file_path);

}

void close_search_engine() {

	/*
	 * free resources if needed ?
	 */

	puts("SEARCH ENGINE : CLOSE");
}
