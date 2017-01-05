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
	
DataFile init_data_file(char* path){
	DataFile data_file;
	data_file.path = path;
	if (is_existing_file(data_file)){
		set_data_file_length(&data_file);
	}
	return data_file;
}

int is_existing_file(DataFile data_file){
	data_file.file = fopen(data_file.path, "r");
	int res = (data_file.file != NULL);
	fclose(data_file.file);
	return res;
}

int is_empty_file(DataFile data_file){
	return (data_file.length == 0);
} 

void set_data_file_length(DataFile* data_file){
	struct stat s;
	stat(data_file->path, &s);
	data_file->length = s.st_size;
}

int get_data_file_extension(DataFile data_file){
	char* ext = strrchr(data_file.path, '.') + 1;
	if (strcmp(ext, "xml") == 0){
    	return TEXT;
	} 
	if (strcmp(ext, "txt") == 0){
		//TODO: separate image and found possibility
    	return IMAGE;
	}
	return -1;
}

char* read_string_from_file(DataFile data_file){
	set_data_file_length(&data_file);
	data_file.file = fopen(data_file.path, "r+");
	printf("%d\n", data_file.length);
	char* string_in_file = (char *) malloc(sizeof(char) * data_file.length);
	for (int i = 0; i < data_file.length; i++){
		char tmp = fgetc(data_file.file);
		string_in_file[i] = tmp;
	}
	fclose(data_file.file);
	return string_in_file;
}


void write_string_in_file(DataFile data_file, char *string) {
	data_file.file = fopen(data_file.path, "w");
	fputs(string, data_file.file);
	fclose(data_file.file);
}

void open_data_file(DataFile* data_file, char* option){
	//data_file->file = fopen(data_file->path, option);
}

void close_data_file(DataFile data_file){
	//fclose(data_file.file);
}
