/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */

#include <stdio.h>
//#include "data_manager.h"
#include "text_finder.h"
#include "image_finder.h"
#include "sound_finder.h"
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

	enum FileType file_type = get_data_file_extension(df);

	switch (file_type){
		case TEXT:
			find_text(df);
		break;

		case IMAGE:
			find_image(df);
		break;

		case SOUND:
			find_sound(df);
		break;

		default : 
			return FILE_TYPE_NOT_SUPPORTED;
		break;
	}

	return SUCCESS;
}
