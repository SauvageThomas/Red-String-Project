/*
 * tools.h
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */

#include <stdio.h>

#ifndef TOOLS_DATA_HANDLER_H_
#define TOOLS_DATA_HANDLER_H_

typedef struct etDataFile{
	FILE* file;
	char* path;
	int length;
}DataFile;

DataFile init_data_file(char* path);
int is_existing_file(DataFile data_file);
int is_empty_file(DataFile data_file);
void set_data_file_length(DataFile* data_file);
char* read_string_from_file(DataFile data_file);
void write_string_in_file(DataFile data_file, char *string);
void close_data_file(DataFile data_file);
void open_data_file(DataFile* data_file, char* option);

#endif /* TOOLS_DATA_HANDLER_H_ */
