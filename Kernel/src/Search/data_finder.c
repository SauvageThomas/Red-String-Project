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

	FILE* file = fopen(file_path, "r");


	if (file == NULL){
		return FILE_NOT_FOUND;
	}

	if (is_empty_file(file_path)){
		fclose(file);
		return EMPTY;
	}

	return SUCCESS;
}