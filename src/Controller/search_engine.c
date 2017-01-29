/*
 ============================================================================
 Name        : search_engine.c
 Author      : Kévin
 Version     :
 Description : Search Engine
 ============================================================================
 */

#include "search_engine.h"


void launch_search_engine(Config config) {

	/*
	 * MANAGE ALL THE SOFTWARE PROCESS
	 */

	init_search_engine(config);
	run_search_engine(config);
	close_search_engine();
}

void init_search_engine(Config config) {

	/*
	 * UPDATE DESCRIPTORS AND INDEX IF NEEDED
	 */
	puts("\n\n ==================================================================");
	puts(" >>>    SEARCH ENGINE : INITITIALIZATION");
	puts("-> checking descriptors...");
	char *path = get_value_of(config, "descriptors");
	chrono();
	Directory dir = get_all_files(get_value_of(config, "path"));


	// Text descriptor update
	check_text_descriptor(path, dir);


	// Image descriptor update
	char *quant = get_value_of(config, "quantification");
	if (quant == NULL) {
		error_config_file();
	}
	size_t n = (size_t) strtol(quant, (char **) NULL, 10);
	check_image_descriptor(path, dir, n);


	// Sound descriptor update
	char *size_window = get_value_of(config, "taille_des_fenetres");
	char *nb_intervalles = get_value_of(config, "nombre_de_barre");
	if (size_window == NULL || nb_intervalles == NULL) {
		error_config_file();
	}
	size_t k = (size_t) strtol(size_window, (char **) NULL, 10);
	size_t m = (size_t) strtol(nb_intervalles, (char **) NULL, 10);
	check_sound_descriptor(path, dir, k, m);


	if(!DEBUG)
		clear_console();
	printf("\n >>>    GENERATING DESCRIPTORS TIME : %ds\n", chrono());
	puts(" >>>    SEARCH ENGINE : READY\n");
}

void run_search_engine(Config config) {

	/*
	 * RUN THE RESEARCH
	 */
	search_gui(config);
}

void close_search_engine() {

	/*
	 * free resources if needed ?
	 */
	puts("\n\n\n ==================================================================");
	puts(" >>>    SEARCH ENGINE : CLOSE\n\n");
}
