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

	return SUCCESS;
}