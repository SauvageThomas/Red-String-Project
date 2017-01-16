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

Descriptor generate_text_descriptor(DataFile df){
	int matrix_length = 0;
	Descriptor descriptor = init_descriptor(df.path);


	char* content = read_string_from_file(df);
	char* new_content = remove_xml(content);
	remove_punctuation(new_content);
	char** words = remove_words(new_content, &matrix_length);


	descriptor.size = strlen(new_content);
	for (int i = 0; i < matrix_length; i++) {
		add_value_hash_map(&(descriptor.map), words[i]);
	}
	return descriptor;
}

void generate_text_descriptors(DataFile df, Directory dir){
	puts("Text files");
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < dir.txt_size; i += 1) {
		Descriptor desc = generate_text_descriptor(dir.txt_files[i]);
		descriptor_to_file(desc, df);
		printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.txt_files[i].path);
	}
}


Descriptor generate_image_descriptor(DataFile df, int quant){
	Descriptor descriptor = init_descriptor(df.path);
	size_t size;
	size_t *quant_array = quantify_file(quant, df, &size);/*
	int max = size;
	size_t *new_array = malloc(max * sizeof(size_t));
	for (int i = 0; i < max; i += 1) {
		int tmp = quant_array[i];
		new_array[i] = tmp;
	}
	*/
	char str[4];
	printf("SIZE = %d\n", size);
	
	descriptor.size = size*2;
	for (int i = 0; i < size ; i += 1) {
		sprintf(str, "%u", quant_array[i]);
	
		//printf("[%d/%u] => %u\n", (i+1), size, quant_array[i]);
		
		add_value_hash_map(&(descriptor.map), str);
	}
	puts("Free new_array");
	free(quant_array);
	return descriptor;
}

void generate_image_descriptors(DataFile df, Directory dir, int quant){
	write_string_in_file(df, ""); //Reset the file
	puts("Image files");
	for (int i = 0; i < dir.image_size; i += 1) {
		puts("debug1");
		Descriptor desc = generate_image_descriptor(dir.image_files[i], quant);
		puts("debug2");
		descriptor_to_file(desc, df);
		puts("debug3");
		printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.image_files[i].path);
	}
}


Descriptor generate_sound_descriptor(DataFile df){
	Descriptor descriptor = init_descriptor(df.path);
	return descriptor;
}

void generate_sound_descriptors(DataFile df, Directory dir){
	write_string_in_file(df, ""); //Reset the file
	puts("Audio files");
	for (int i = 0; i < dir.audio_size; i += 1) {
		Descriptor desc = generate_sound_descriptor(dir.audio_files[i]);
		descriptor_to_file(desc, df);
		printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.audio_files[i].path);
	}
}

//Appends the descriptor at the end of the file
void descriptor_to_file(Descriptor descriptor, DataFile df) {
	//puts("Desc to file");
	if (descriptor.map == NULL) {
		return;
	}
	//puts("Saving the descriptor ...");

	char *result = malloc(descriptor.size);
	printf("malloc size : %u\n", descriptor.size);
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

