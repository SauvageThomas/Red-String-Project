/*
 * data_finder.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */


#include <stdio.h>
#include "data_finder.h"
#include "../Tools/report.h"
#include "../Tools/data_handler.h"



int search_data(char* file_path){

	DataFile df = init_data_file(file_path);
	
	if (!is_existing_file(df)){
		return FILE_NOT_FOUND;
	}

	if (is_empty_file(df)){
		return EMPTY;
	}

	int file_type = get_data_file_extension(df);

	if (file_type == 1){

		// Extract method in text_finder.c :
		printf("XML FILE\n");
		char* content = read_string_from_file(df);
		//TODO: remove "<...>", ".?!...", word < 3char
		//TODO: compare with index and get the similar files 

	}

	else if (file_type == 2){

		// Extract method in image_finder.c :
		printf("IMAGE FILE\n");
		//TODO: regroup and count all pixels
		//TODO: compare with index and get the similar files 

	}

	else if (file_type == 3){

		// Extract method in sound_finder.c :
		printf("SOUND FILE\n");
		//TODO: regroup and count all pixels
		//TODO: compare with index and get the similar files 

	}

	else {
		return FILE_TYPE_NOT_SUPPORTED;
	}

	return SUCCESS;
}