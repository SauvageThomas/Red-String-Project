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

void update_index(){


	/*
	* UPDATE THE INDEX FILE
	*/

	//TODO: 
	//pour chaque fichier
	//	récupérer le nom
	//	


	char* path = "../../res/descriptors/text_descriptors";
	DataFile file = init_data_file(path);
	char* text = read_string_from_file(file);
	//printf("%s\n",read_string_from_file(file));
	for(int i = 0; 	 i< file.length; i++){
		if(text[i]=='>')
			printf("----------------------------------\n");
		printf("%c",text[i]);
	}

	  
	
	puts("INDEX FILE UPDATED.");
}

int main(){
	puts("--> test index generator\n");
	//update_index();
	MapOfMap map;
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
	HashMap hashMap = *get_hashMap_with_key(map, "aa");
	//printf("Test ----> : %s\n", pop_value_hash_map(&hashMap));
	//free_map_of_map(map);
}


