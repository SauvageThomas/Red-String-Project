/*
 ============================================================================
 Name        : report.c
 Author      : Kévin
 Version     :
 Description : manage all the reports of the software
 ============================================================================
 */

#include "report.h"

void show_search_report(int res){
	switch(res){
		case SUCCESS :
			puts("Search done successfully !");
		break;

		case EMPTY : 
		 	puts("Search aborted : empty file !");
		break;

		case FILE_NOT_FOUND : 
		 	puts("Search aborted : file not found !");
		break;

		case FILE_TYPE_NOT_SUPPORTED : 
		 	puts("Search aborted : data type not supported !");
		break;

		default :
			puts("Search aborted : unexpected error !");
		break;
	}
}