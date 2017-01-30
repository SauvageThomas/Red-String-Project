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
			puts("\nSearch done successfully !");
		break;

		case EMPTY : 
		 	puts("\nSearch aborted : empty file !");
		break;

		case FILE_NOT_FOUND : 
		 	puts("\nSearch aborted : file not found !");
		break;

		case FILE_TYPE_NOT_SUPPORTED : 
		 	puts("\nSearch aborted : data type not supported !");
		break;

		default :
			puts("\nSearch aborted : unexpected error !");
		break;
	}
}