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

#include "../Tools/hash_map.h"
#include "descriptor_generator.h"
#include "descriptor_tools.h"
#include "../Data/constant.h"
#include "../Tools/data_handler.h"
#include "../Tools/hash_map.h"

int check_files() {
	//TODO: check every file last modification date
	return 1;
}

int check_descriptor(DataFile df, DataFile *data_files, size_t size) {
	if (df.length == 0) {
		puts("no descriptor found !");
		return 1;
	}
	//return 1;
	puts("Have to check every file...");

	char *content = read_string_from_file(df);

	int size_desc;

	Descriptor *desc = extract_all_descriptor(content, &size_desc);
	//printf("size desc : %d and nb files %u\n", size_desc, size);
	if (size != size_desc) {
		puts("size !=");
		return 1;
	}
	//puts("size ok");

	//For each file
	for (int i = 0; i < size; i += 1) {

		//printf("<%s> and <%s>\n", desc[i].file_name, data_files[i].path);
		//printf("<%d> and <%d>\n", strlen(desc[i].file_name),
				//strlen(data_files[i].path));

		//If it's not a different file
		if (strlen(desc[i].file_name) == strlen(data_files[i].path)) {
			for (int j = 0; j < strlen(desc[i].file_name); j += 1) {

				/*printf("<%c> and <%c>\n", desc[i].file_name[j],
						data_files[i].path[j]);*/

				if (desc[i].file_name[j] != data_files[i].path[j]) {
					puts("wrong");

					free(desc);
					free(content);
					return 1;
				}
			}
		}

		DataFile ressource = init_data_file(desc[i].file_name);
		if (ressource.date > df.date) {
			puts("Not up2date");

			free(desc);
			free(content);
			return 1;
		}
		free_map(desc[i].map);
		//puts(desc.file_name);
		//printf("ressource %u -- desc %u\n", ressource.date, df.date);

	}

	puts("file ok");
	free(desc);
	free(content);
	return 0;
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

