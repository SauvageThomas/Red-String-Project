/*
 ============================================================================
 Name        : index_generator.c
 Author      : Pierre
 Version     :
 Description : Generate index file
 ============================================================================
 */

#include "index_generator.h"
#include "../Tools/data_handler.h"
#include "../Tools/map_of_map.h"
#include "../Data/constant.h"
#include <string.h>

void update_index(){

	/*
	* CREATE OR UPDATE THE INDEX FILE
	*/


	char* pathDescriptor = "../../../data/descriptors/text_descriptors";
	DataFile fileSource = init_data_file(pathDescriptor);
	char* text = read_string_from_file(fileSource);

	char* fileName = malloc(KSIZE +1);
	char* wordCurent = malloc(KSIZEWORD-50);
	char* numberOccurenceCurent = malloc(sizeof(int));
	int intNumberOccurenceCurent;
	int isFileName = 0;
	int isText = 0;
	int isWordCurent = 0;
	int isNumberOccurenceCurent = 0;
	char* pattern = "%c";
	MapOfMap map;
	init_MapOfMap(&map);
	int test = 0;
	char* tmp;

	for(int i = 0; 	 i< fileSource.length; i++){
		if(text[i]=='>'){	
			test ++;
			fileName="";
			fileName =  malloc(KSIZE + 1);
			isWordCurent = 0;
			isFileName = 1;
			continue;
		}
		if(isFileName == 1 && text[i]!='\n'){
			tmp = malloc(sizeof(char));
			sprintf(tmp,"%c",text[i]);
			strcat(fileName, tmp);
			continue;
		}
		if( isFileName == 1 && text[i]=='\n'){
			isFileName = 0;
			isWordCurent = 1;
			wordCurent="";
			wordCurent =  malloc(KSIZEWORD);
			continue;
		}
		if(isWordCurent == 1 && text[i] != ' ' && text[i] != '\n'){
			tmp = malloc(sizeof(char));
			sprintf(tmp,"%c",text[i]);
			strcat(wordCurent, tmp);
			continue;
		}
		if(isWordCurent == 1 && text[i] == ' ' ){
			isWordCurent = 0;
			isNumberOccurenceCurent = 1;
			numberOccurenceCurent="";
			numberOccurenceCurent =  malloc(KSIZEWORD);
			continue;
		}
		if(isNumberOccurenceCurent == 1 && text[i] != '\n'){
			tmp = malloc(sizeof(char));
			sprintf(tmp,"%c",text[i]);
			strcat(numberOccurenceCurent, tmp);
			continue;
		}
		if(isNumberOccurenceCurent == 1 && text[i] == '\n'){
			sscanf(numberOccurenceCurent,"%d", &intNumberOccurenceCurent);
			add_value_MapOfMap(&map, wordCurent, fileName,intNumberOccurenceCurent);
			isWordCurent = 1;
			isNumberOccurenceCurent = 0;
			wordCurent="";
			wordCurent =  malloc(KSIZEWORD);
			continue;
		}
	}


	FILE* fileIndex=  fopen("../../../data/descriptors/text_index", "w+");

    if (fileIndex != NULL)
    {
		if(map!=NULL){
			fputs( pop_value_MapOfMap(&map), fileIndex);
		}
		while(map!=NULL){
			fputs(pop_value_MapOfMap(&map),fileIndex); 
		}	
    	//fclose(fileIndex);
    }
	
	puts("INDEX FILE UPDATED.");
}

