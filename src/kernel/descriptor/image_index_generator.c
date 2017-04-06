/*
 ============================================================================
 Name        : index_image_generator.c
 Author      : Pierre
 Version     :
 Description : Generate index file
 ============================================================================
 */

#include "image_index_generator.h"
#include "../Search/data_manager.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* calculate_index_3_color(FILE* file, size_t size_x, size_t size_y){
	size_t sum_red = 0;
	size_t sum_green = 0;
	size_t sum_blue = 0;
	int current_val = 0;
	int current_char ="";
	int nb_pixel = 0;
	while (current_char != EOF){
		current_char = getc(file);

		if(current_char == ' ' || current_char == '\n'){
			if(nb_pixel<= size_x * size_y)
				sum_red += current_val;

			else if(nb_pixel<= 2* (size_x * size_y))
				sum_green += current_val;
			
			else 
				sum_blue += current_val;
			current_val = 0;
			nb_pixel += 1;
		}
		else
			current_val = current_val * 10 + current_char - '0';
	}
	fclose(file);
	char* result = (char*) malloc(sizeof(char)*14);
	sprintf(result, "%d %d %d\n\n", sum_red/size_x/size_y, sum_green/size_x/size_y, sum_blue/size_x/size_y);
	return result;
}


char* calculate_index_1_color(FILE* file, size_t size_x, size_t size_y){
	size_t color = 0;
	int current_val = 0;
	int current_char ="";
	int nb_pixel = 0;
	while (current_char != EOF){
		current_char = getc(file);

		if(current_char == ' ' || current_char == '\n'){
			color += current_val;
			current_val = 0;
			nb_pixel += 1;
		}else
			current_val = current_val * 10 + current_char - '0';
	}
	fclose(file);
	char* result = (char*) malloc(sizeof(char)*14);
	sprintf(result, "%d\n\n", color/size_x/size_y);
	return result;
}


char* calculate_index(FILE* file){
	int size_x = 0;
	int size_y = 0;
	int nb_color = 0;
	int tmp = 0;
	int current_char ="";
	
	while (current_char != '\n'){
		current_char = getc(file);
		if(current_char == ' ' || nb_color != 0)
			tmp +=1;
		else{
			if(tmp == 0)
				size_x = size_x * 10 + current_char - '0';
	
			if(tmp == 1)
				size_y = size_y * 10 + current_char - '0';

			if(tmp == 2)
				nb_color = 0 + current_char - '0';
		}
	}

	if(nb_color == 3)
		return calculate_index_3_color(file, size_x, size_y);
	if(nb_color == 1)
		return calculate_index_1_color(file, size_x, size_y);
	return "";
}


char* open_image_txt(char* image_file_path){
	FILE* file = NULL;
	char* text_path = image_file_path;
	text_path[strlen(text_path)-3] = 't';
	text_path[strlen(text_path)-2] = 'x';
	text_path[strlen(text_path)-1] = 't';

	file = fopen(text_path, "r");
	if (file != NULL){
		char* result = (char*) malloc(strlen(text_path) + 3 + sizeof(char)*14);
   		sprintf(result, ">%s\n\n%s", text_path, calculate_index(file));
		//printf("%s",result);
		return result;
	}else	
		printf("Impossible d'ouvrir le fichier %s\n",text_path);
	return "";
}

void update_index_image(char *_path, char *index_path) {
	/*
	 * CREATE OR UPDATE THE INDEX FILE IMAGE
	 */

	puts("Debut de l'update image index\n\n");

	Directory dir = get_all_files(_path);
	printf("Nombre d'image dans le répertoire : %d\n",dir.image_size);
	int nb = 0;
	char* result = "";
	char* tmp = "";

	for (int i = 0; i < dir.image_size; i += 1) {
		tmp = (char*) malloc(strlen(result) + 150);
		sprintf(tmp, "%s%s", result, open_image_txt(dir.image_files[i].path));
		result = (char*) malloc(strlen(tmp)+1);
		strcpy(result, tmp);
		nb += 1;
	}
	//printf("%s", result);
	 
	
	FILE* fileIndex = fopen(index_path, "w+");

	if (fileIndex != NULL) {
			fputs(result, fileIndex);
	}
	

	//printf("Dossier : %s\n",_path);
	//printf("Index : %s\n",index_path);
	puts("INDEX FILE IMAGE UPDATED.");
}



