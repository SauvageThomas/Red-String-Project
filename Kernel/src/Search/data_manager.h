/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */


#ifndef DESCRIPTOR_DATA_MANAGER_H_
#define DESCRIPTOR_DATA_MANAGER_H_


enum FileType {
	TEXT, IMAGE, SOUND
};

int search_data(char* file_path);

#endif
