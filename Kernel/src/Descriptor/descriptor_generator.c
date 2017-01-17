/*
 * descriptor_generator.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../Descriptor/descriptor_tools.h"
#include "descriptor_generator.h"
#include "../Search/data_manager.h"
#include "../Data/constant.h"
#include "../Tools/data_handler.h"
#include "../Tools/hash_map.h"
#include "../Search/text_finder.h"
#include "../Search/image_finder.h"

int check_files() {
	//TODO: check every file last modification date
	return 1;
}

int check_descriptor(DataFile df, DataFile *data_files, size_t size) {
	if (df.length == 0) {
		puts("no descriptor found !");
		return 1;
	}
	puts("Have to check every file...");

	char *content = read_string_from_file(df);

	int size_desc;

	Descriptor *desc = extract_first_descriptor(content, &size_desc);
	printf("size desc : %d and nb files %u\n", size_desc, size);
	if (size != size_desc) {
		return 1;
	}

	for (int i = 0; i < size; i += 1) {
		//puts(content);

		DataFile ressource = init_data_file(desc[0].file_name);
		exit(0);
		//puts(content);

		//puts(desc.file_name);
		//printf("ressource %u -- desc %u\n", ressource.date, df.date);
		if (ressource.date > df.date) {
			puts("Not up2date");
			exit(0);
		}
	}

	return check_files();
}

Descriptor init_descriptor(char* path) {
	time_t rawtime = time(NULL);
	//printf("%u\n", rawtime);

	Descriptor descriptor = { .map = NULL, .date = rawtime };
	strcpy(descriptor.file_name, path);
	return descriptor;
}

//Appends the descriptor at the end of the file
void descriptor_to_file(Descriptor descriptor, DataFile df) {
	//puts("Desc to file");
	if (descriptor.map == NULL) {
		puts("None");
		return;
	}
	//puts("Saving the descriptor ...");

	char *result = malloc(descriptor.size);
	if (result == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}

	char date[50];
	sprintf(date, "%u\n", descriptor.date);

	//printf("%u vs %s\n", descriptor.date, date);
	/*
	 time(&descriptor.date);
	 time_t tminfo = localtime(&descriptor.date);
	 */

	strcpy(result, ">");
	strcat(result, descriptor.file_name);/*
	 strcat(result, "?");
	 strcat(result, date);*/
	strcat(result, "\n");
	strcat(result, "\n");

	while (descriptor.map != NULL) {
		char *tmp = pop_value_hash_map(&(descriptor.map));
		//printf("to file => %s\n", tmp);
		strcat(result, tmp);
	}
	append_string_in_file(df, result);

	free_map(descriptor.map);
	free(result);
	result = NULL;
}

