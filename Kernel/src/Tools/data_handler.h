/*
 * tools.h
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */

#include <stdio.h>
#include "../Search/data_manager.h"
x
#ifndef TOOLS_DATA_HANDLER_H_
#define TOOLS_DATA_HANDLER_H_

typedef struct etDataFile {
	FILE* file;
	char* path;
	int length;
	char *type;
} DataFile;

typedef struct {
	DataFile *txt_files;
	size_t txt_size;
	DataFile *audio_files;
	size_t audio_size;
	DataFile *image_files;
	size_t image_size;
} Directory;

DataFile init_data_file(char* path);
int is_existing_file(DataFile data_file);
int is_empty_file(DataFile data_file);
void set_data_file_length(DataFile* data_file);
int get_data_file_extension(char *file_name);
char* read_string_from_file(DataFile data_file);
void write_string_in_file(DataFile data_file, char *string);
void append_string_in_file(DataFile data_file, char *string);
void purge_buffer();
int get_secure_input(char* buffer, size_t size);

#endif /* TOOLS_DATA_HANDLER_H_ */
