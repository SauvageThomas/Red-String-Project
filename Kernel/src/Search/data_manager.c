/*
 * data_manager.c
 *
 *  Created on: 5 d�c. 2016	
 *      Author: THOMAS
 */

#include <stdio.h>
//#include "data_manager.h"
#include "text_finder.h"
#include "image_finder.h"
#include "sound_finder.h"
#include "../Tools/report.h"
#include "../Tools/data_handler.h"
#include "../Data/constant.h"


int search_data( const char* file_path){
	EMBED_BREAKPOINT;
	DataFile df = init_data_file(file_path);
	EMBED_BREAKPOINT;	

	if (!is_existing_file(df)){
		printf("not found : %s\n", file_path);
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
