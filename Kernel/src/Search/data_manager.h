/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */


#ifndef DESCRIPTOR_DATA_MANAGER_H_
#define DESCRIPTOR_DATA_MANAGER_H_

#include "../GUI/functions.h"

enum FileType {
	TEXT, IMAGE, SOUND
};

int search_data( const char* file_path, Config config);

#endif
