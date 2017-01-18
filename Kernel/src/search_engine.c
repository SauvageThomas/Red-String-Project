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

#include "GUI/functions.h"
#include "search_engine.h"
#include "Descriptor/text_descriptor_generator.h"
#include "Descriptor/image_descriptor_generator.h"
#include "Descriptor/sound_descriptor_generator.h"
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

char* strcat_path(char* path, char* file_name) {
	/*
	 * Return concat path + filename
	 */
	char* full_path = malloc(KSIZE);
	sprintf(full_path, "%s%s", path, file_name);
	return full_path;
}

void check_text_descriptor(char* path, Directory dir) {
	char* full_path = strcat_path(path, "text_descriptors");
	DataFile df = init_data_file(full_path);
	int updated = check_descriptor(df, &dir.txt_files, dir.txt_size);
	if (updated) {
		puts("upadting ...");
		generate_text_descriptors(df, dir);
		update_index();
	}
}

void check_image_descriptor(char* path, Directory dir, int n) {
	char* full_path = strcat_path(path, "image_descriptors");
	DataFile df = init_data_file(full_path);
	int updated = check_descriptor(df, &dir.image_files, dir.image_size);
	if (updated) {
		puts("upadting ...");
		generate_image_descriptors(df, dir, n);
		update_index();
	}
}

void check_sound_descriptor(char* path, Directory dir, int k, int m) {
	char* full_path = strcat_path(path, "sound_descriptors");
	DataFile df = init_data_file(full_path);
	int updated = check_descriptor(df);
	if (updated) {
		generate_sound_descriptors(df, dir, k, m);
	}
}
void init_search_engine(Config config) {

	/*
	 * UPDATE DESCRIPTORS AND INDEX IF NEEDED
	 */
	puts("------------------------------------------------------------------");
	puts("*   *   *   SEARCH ENGINE : INITITIALIZATION");

	//puts("-> checking descriptors...");
	char *path = get_value_of(config, "descriptors");

	chrono();

	Directory dir = get_all_files(get_value_of(config, "path"));

	check_text_descriptor(path, dir);

	char *quant = get_value_of(config, "quantification");
	if (quant == NULL) {
		error_config_file();
	}

	size_t n = (size_t) strtol(quant, (char **) NULL, 10);
	check_image_descriptor(path, dir, n);

	char *size_window = get_value_of(config, "taille_des_fenetres");
	char *nb_intervalles = get_value_of(config, "nombre_de_barre");
	if (size_window == NULL || nb_intervalles == NULL) {
		error_config_file();
	}
	size_t k = (size_t) strtol(size_window, (char **) NULL, 10);
	size_t m = (size_t) strtol(nb_intervalles, (char **) NULL, 10);
	check_sound_descriptor(path, dir, k, m);

	printf("Generating descriptors took %ds\n", chrono());

	puts("Search Engine is ready !!");
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
