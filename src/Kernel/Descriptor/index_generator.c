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
	* UPDATE THE INDEX FILE
	*/


	char* pathDescriptor = "../../../data/descriptors/text_descriptors_v2";
	DataFile fileSource = init_data_file(pathDescriptor);
	char* text = read_string_from_file(fileSource);

	char* pathIndex = "../../../data/descriptors/text_index";
	DataFile fileDestination = init_data_file(pathDescriptor);

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
	
	if(map!=NULL){
		write_string_in_file(fileDestination, pop_value_MapOfMap(&map));
		puts("mamamiya");
	}
	while(map!=NULL){
		append_string_in_file(fileDestination,pop_value_MapOfMap(&map)); 
		puts("heuuu...");
	}
	  
	

	puts("INDEX FILE UPDATED.");
}

/*
int main(){
	puts("--> test index generator\n");
	update_index();
/*	MapOfMap map;
	init_MapOfMap(&map);
	add_value_MapOfMap(&map, "aa", "Fichier1", 11);
	add_value_MapOfMap(&map, "bb", "Fichier2", 22);
	add_value_MapOfMap(&map, "cc", "Fichier2", 33);
	add_value_MapOfMap(&map, "aa", "Fichier3", 111);
	add_value_MapOfMap(&map, "aa", "Fichier4", 12);
	add_value_MapOfMap(&map, "aa", "Fichier45",777);
	add_value_MapOfMap(&map, "aa", "Fichier42",7897);
	add_value_MapOfMap(&map, "dd", "Fichier5", 4);
	add_value_MapOfMap(&map, "bb", "Fichier6", 222);
	/*while(!is_map_of_map_empty(map)){
		printf("%s\n",pop_value_map_of_map(&map)); 

	}	*/
	//HashMap hashMap = *get_hashMap_with_key(map, "aa");
	//printf("Test ----> : %s\n", pop_value_hash_map(&hashMap));
	//free_map_of_map(map);
//}


