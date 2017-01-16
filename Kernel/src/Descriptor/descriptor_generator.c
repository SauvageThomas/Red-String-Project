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

#include "descriptor_generator.h"
#include "../Search/data_manager.h"
#include "../Data/constant.h"
#include "../Tools/data_handler.h"
#include "../Tools/hash_map.h"
#include "../Search/text_finder.h"
#include "../Search/image_finder.h"


int check_files(){
	//TODO: check every file last modification date
	return 1;
}

int check_descriptor(DataFile df) {
	if (is_existing_file(df) || is_empty_file(df)) {
		puts("no descriptor found !");
		puts("hey !!!!");
		return 1;
	}		
	puts("Have to check every file...");
	
	return check_files();
}


Descriptor init_descriptor(char* path){
	time_t rawtime;
	time(&rawtime);
	Descriptor descriptor = { .map = NULL, .file_name = path, .time =localtime(&rawtime) };
	return descriptor;
}

//Appends the descriptor at the end of the file
void descriptor_to_file(Descriptor descriptor, DataFile df) {
	//puts("Desc to file");
	if (descriptor.map == NULL) {
		return;
	}
	//puts("Saving the descriptor ...");

	char *result = malloc(descriptor.size);
	if (result == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}
	strcpy(result, ">");
	strcat(result, descriptor.file_name);
	strcat(result, "?");
	strcat(result, asctime(descriptor.time));

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

