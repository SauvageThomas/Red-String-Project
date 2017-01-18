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
/*
int main(){
	puts("--> test index generator\n");
	update_index();
	/*map_of_map map;
	init_map_of_map(&map);
	add_value_map_of_map(&map, "aa", "Fichier1", 11);
	add_value_map_of_map(&map, "bb", "Fichier2", 22);
	add_value_map_of_map(&map, "cc", "Fichier2", 33);
	add_value_map_of_map(&map, "aa", "Fichier3", 111);
	add_value_map_of_map(&map, "aa", "Fichier4", 12);
	add_value_map_of_map(&map, "aa", "Fichier45", 777);
	add_value_map_of_map(&map, "dd", "Fichier5", 4);
	add_value_map_of_map(&map, "bb", "Fichier6", 222);
	while(!is_map_of_map_empty(map)){
		printf("%s\n",pop_value_map_of_map(&map)); 
	}
	*/
//}


