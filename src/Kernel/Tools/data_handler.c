/*
 * tools.c
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include "data_handler.h"
#include "../Data/constant.h"

// permet d'initialiser une structure DataFile à partir d'un chemin
DataFile init_data_file(char* path) {
	DataFile data_file;
	data_file.path = malloc(strlen(path) + 1);

	if (data_file.path == NULL) {
		fprintf(stderr, "Malloc in init_data_file failed %s\n", strerror(errno));
	}
	strcpy(data_file.path, path);
	data_file.length = 0; //Init if the file does not exist

	if (is_existing_file(data_file)) {
		set_data_file_length(&data_file);
	}
	return data_file;
}

// permet de savoir si un fichier existe
int is_existing_file(DataFile data_file) {
	data_file.file = fopen(data_file.path, "r");
	int res = (data_file.file != NULL);
	if (res) {
		fclose(data_file.file);
	}
	return res;
}

//permet de savoir si le fichier appelé est vide
int is_empty_file(DataFile data_file) {
	return (data_file.length == 0);
}

//permet d'initialiser la taille d'un fichier 
void set_data_file_length(DataFile* data_file) {
	struct stat s;
	stat(data_file->path, &s);
	data_file->date = s.st_mtime;
	data_file->length = s.st_size;
}

//retourne un entier pour connaître le type d'un fichier, à partir de son extension
int get_data_file_extension(char *file_name) {

	if (strlen(file_name) < 4) {// un nom de fichier a au moins 4 caractères !
		return -1;
	}

	char *ext = strrchr(file_name, '.') + 1;

	if (!strcmp(ext, "xml") /*|| !strcmp(ext, "txt")*/) {
		return TEXT;
	} else if (!strcmp(ext, "wav")) {
		return SOUND;
	} else if (!strcmp(ext, "jpg") || !strcmp(ext, "bmp")) {
		return IMAGE;
	}
	return -1;
}
//récupère le contenu d'un fichier quel qu'il soit et l'enregistre dans un tableau dynamique de caractère
char* read_string_from_file(DataFile data_file) {
	set_data_file_length(&data_file);
	data_file.file = fopen(data_file.path, "r+");
	char* string_in_file = malloc(data_file.length + 1);
	if (string_in_file == NULL) {
		fprintf(stderr, "Malloc in read_string_from_file failed %s\n", strerror(errno));
	}
	int i = 0;
	char c;
	do{// récupère le contenu du fichier tant qu'on a pas atteint la fin du fichir (EOF)
		c = getc(data_file.file);
		if (c != EOF){
			string_in_file[i] = c;
			i ++;
		}
	}while(c != EOF);
	
	string_in_file[i] = '\0';
	fclose(data_file.file);
	return string_in_file;
}

// écrit dans un fichier ( son pointeur compris dans la structure DataFile ) avec le contenu de la chaîne de caractère 
void write_string_in_file(DataFile data_file, char *string) {
	data_file.file = fopen(data_file.path, "w");
	fputs(string, data_file.file);
	fclose(data_file.file);
}

//ajoute une chaîne de caractère dans le fichier sélectionné ( contenu dans la structure DataFile )
void append_string_in_file(DataFile data_file, char *string) {
	data_file.file = fopen(data_file.path, "a");
	fputs(string, data_file.file);
	fclose(data_file.file);
}

//nettoie le tableau utilisé en C pour la récupération de données de façon à éviter les problèmes de conservation des données
void purge_buffer() {
	int c = 0;
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

// récupère les données de l'entrée standard de manière sécurisée
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
	return res;
}

char* strcat_path(char* path, char* file_name) {
	/*
	 * Return concat path + filename
	 */
	char* full_path = malloc(KSIZE);
	sprintf(full_path, "%s%s", path, file_name);
	return full_path;
}
