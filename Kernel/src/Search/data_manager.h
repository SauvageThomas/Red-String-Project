/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */


#ifndef DESCRIPTOR_DATA_MANAGER_H_
#define DESCRIPTOR_DATA_MANAGER_H_

<<<<<<< HEAD
#include "../GUI/functions.h"
=======
#include "../Data/constant.h"
>>>>>>> 8d4327f3c79bf41ed9c13cf775df01b92ab4a74a

enum FileType {
	TEXT, IMAGE, SOUND
};

<<<<<<< HEAD
int search_data( const char* file_path, Config config);
=======
int search_data(Config config, const char* file_path);
>>>>>>> 8d4327f3c79bf41ed9c13cf775df01b92ab4a74a

#endif
