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


