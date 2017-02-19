
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include "../Data/constant.h"
#include "../Data/data_base.h"

#ifndef TOOLS_DATA_HANDLER_H_
#define TOOLS_DATA_HANDLER_H_

typedef struct etDataFile {
	FILE* file;
	char* path;
	int length;
	char *type;
	time_t date;
} DataFile;

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
char* strcat_path(char* path, char* file_name);

#endif /* TOOLS_DATA_HANDLER_H_ */
