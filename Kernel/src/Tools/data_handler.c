/*
 * tools.c
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */
#include <stdio.h>
#include <stdlib.h>
	
int file_length_retriever( char* path){
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
	FILE * file= NULL;
	int size_file, i=0, test;
	int tmp;
	file=fopen (path, "r");
	if (file!=NULL){
		size_file=file_length_retriever(path);
		char* string_in_file=(char*)malloc((size_file)*sizeof(char));
		do {
			tmp=fgetc(file);
			if (tmp!=EOF)
				string_in_file[i]=tmp;
			else test=1;
			i++;
		}while(test==0);
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

int main(){
	int size=file_length_retriever("../Data/Test/test_read_data_from_file_2");
	char* string_in_file=(char*)malloc((size)*sizeof(char));
	char* string_in_file2=(char*)malloc((size)*sizeof(char));
	string_in_file=read_string_from_file("../Data/Test/test_read_data_from_file_2");
	for (int j=0; j<size; j++)
		printf("%c", string_in_file[j]);
	printf("\n");
	write_string_in_file("../Data/Test/test_read_data_from_file_4", string_in_file);
	string_in_file2=read_string_from_file("../Data/Test/test_read_data_from_file_4");
	for (int j=0; j<size; j++)
		printf("%c", string_in_file2[j]);
	printf("\n");
	return 0;
}
