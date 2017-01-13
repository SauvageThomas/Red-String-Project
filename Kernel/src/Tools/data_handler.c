/*
 * tools.c
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "data_handler.h"
#include "../Data/constant.h"

DataFile init_data_file(char* path) {
	DataFile data_file;
	data_file.path = path;
	data_file.length = 0; //Init if the file does not exist

	if (is_existing_file(data_file)) {
		set_data_file_length(&data_file);
	}
	return data_file;
}

int is_existing_file(DataFile data_file) {
	data_file.file = fopen(data_file.path, "r");
	int res = (data_file.file != NULL);
	if (res) {
		fclose(data_file.file);
	}
	return res;
}

int is_empty_file(DataFile data_file) {
	return (data_file.length == 0);
}

void set_data_file_length(DataFile* data_file) {
	struct stat s;
	stat(data_file->path, &s);
	data_file->length = s.st_size;
}

int get_data_file_extension(DataFile data_file) {
	char* ext = strrchr(data_file.path, '.') + 1;
	if (!strcmp(ext, "xml") || !strcmp(ext, "txt")) {
		return TEXT;
	} else if (!strcmp(ext, "bin") || !strcmp(ext, "wav")) {
		//TODO: separate image and found possibility
		return SOUND;
	} else if (!strcmp(ext, "jpg") || !strcmp(ext, "bmp")) {
		//TODO: separate image and found possibility
		return IMAGE;
	}
	return -1;
}

char* read_string_from_file(DataFile data_file) {
	set_data_file_length(&data_file);
	data_file.file = fopen(data_file.path, "r+");
	char* string_in_file = (char *) malloc(sizeof(char) * data_file.length);

	int i = 0;
	int c;

	while ((c = getc(data_file.file)) != EOF) {
		string_in_file[i] = c;
		i += 1;
	}
	string_in_file[i] = '\0';

	fclose(data_file.file);
	return string_in_file;
}

void write_string_in_file(DataFile data_file, char *string) {
	data_file.file = fopen(data_file.path, "w");
	printf("%d\n", data_file.file == NULL);
	fputs(string, data_file.file);
	fclose(data_file.file);
}

void purge_buffer() {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

int get_secure_input(char* buffer, size_t size) {
	printf(">>");
	int res = 1;

	int c = getchar();
	int i = 0;
	while (c != '\n' && c != EOF) {
		if (i < size - 1) {
			buffer[i] = c;
			i += 1;
		} else {
			res = 0;
		}
		c = getchar();

	}
	buffer[i] = '\0';
	printf("RES : %d\n", res);
	return res;
}
