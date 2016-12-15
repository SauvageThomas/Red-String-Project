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
		printf("Le fichier %s n'a pas pu être ouvert ou n'existe pas !\n", path);
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
		printf("Le fichier %s n'a pas pu être ouvert ou n'existe pas !\n", path);
	return "vide !";
}


void write_string_in_file(char *path, char *string) {
	FILE * file= NULL;
	file=fopen (path, "w+");// si on veut mettre à jour, sinon juste w
	if (file!=NULL){
		fputs( string, file);}
	else
		printf("Le fichier %s n'a pas pu être crée ou l'on a pas pu écrire dedans !\n", path);
	fclose(file);
}

