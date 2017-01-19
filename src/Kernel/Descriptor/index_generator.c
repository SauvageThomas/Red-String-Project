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

void update_index(){


	/*
	* UPDATE THE INDEX FILE
	*/


	char* path = "../../res/descriptors/text_descriptors";
	DataFile file = init_data_file(path);
	char* text = read_string_from_file(file);
	//printf("%s\n",read_string_from_file(file));
	char* fileName = malloc(KSIZE +1);
	char* wordCurent = malloc(KSIZEWORD +1);
	char* numberOccurenceCurrent = malloc(sizeof(int));
	int isFileName = 0;
	int isDate = 0;
	int isText = 0;
	int isWordCurent = 0;
	int isNumberOccurenceCurrent = 0;
	/*for(int i = 0; 	 i< file.length; i++){
		if(text[i]=='>'){
			isFileName = 1;
			
		}
		if( isFileName == 1 && text[i]=='?'){
			isFileName = 0;
			isDate = 1;
		}
		if(isDate == 1 && text[i]=='\n')
			isDate ==0;
		if(isFileName == 1 )
			printf("%c",text[i]);
	}*/
	char* pattern = "%c";
	MapOfMap map;
	init_MapOfMap(&map);
/*
	for(int i = 0; 	 i< file.length; i++){
		if(text[i]=='>'){
			fileName = "";
			isFileName = 1;
			
		}
		if(isFileName == 1 && text[i]!='?'){
			printf("%c",text[i]);
			sprintf(fileName, pattern,text[i]);
		}
		if( isFileName == 1 && text[i]=='?'){
			isFileName = 0;
			isDate = 1;
		}
		if(isDate == 1 && text[i]=='\n'){
			isDate = 0;
			isText = 1;
			isWordCurrent = 1;
		}
		
		if(isText == 1 && isWordCurrent == 1 && text[i] != " "){
			sprintf(wordCurent, pattern,text[i]);
		}
		if(isText == 1 && isWordCurrent == 1 && text[i] == " " ){
			isWordCurrent = 0;
			isNumberOccurenceCurrent = 1;
		}
		if(isText == 1 && isNumberOccurenceCurrent == 1 && text[i] != '\n'){
			sprintf(numberOccurenceCurrent, pattern,text[i]);
		}
		if(isText == 1 && isNumberOccurenceCurrent == 1 && text[i] == '\n'){
			add_value_MapOfMap(&map, wordCurent, fileName, strtok(numberOccurenceCurrent));
		}

	
			
			
	}
*/
	  
	
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


