/*
 * tools.c
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */
#include <stdio.h>
#include <stdlib.h>
	

int is_empty_file(char* path){
	return (file_length_retriever(path) == 0);
} 
int file_length_retriever(char* path){
	int size;
	FILE * file= NULL;
	file=fopen (path, "r");
	if (file!=NULL){
		fseek(file, 0, SEEK_END);
		size= ftell(file);
		fseek(file, 0, SEEK_SET);
		fclose(file);}
	else 
		printf("the file  %s can't be opened or doesn't exist !\n", path);
	return size;
}

char* read_string_from_file(char *path){
	FILE* file = fopen(path, "r");
	if (file != NULL){
		int size_file = file_length_retriever(path);
		char* string_in_file = (char *) malloc(sizeof(char) * size_file);
		for (int i = 0; i < size_file; i++){
			 string_in_file[i] = fgetc(file);
		}
		fclose(file);
		return string_in_file;
	}
	else
		printf("the file  %s can't be opened or doesn't exist !\n", path);
	return "empty !";
}


void write_string_in_file(char *path, char *string) {
	FILE * file= NULL;
	file=fopen (path, "w+");// if we want to update, else just w
	if (file!=NULL){
		fputs( string, file);}
	else
		printf("the file %s can't be created or we can't add text!\n", path);
	fclose(file);
}