/*
 * functions.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#ifndef GUI_FUNCTIONS_H_
#define GUI_FUNCTIONS_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../model/tools/data_handler.h"
#include "../model/tools/hash_map.h"
#include "../model/data/password.h"
#include "../model/data/constant.h"
#include "../model/data/config.h"
#include "../model/search/data_manager.h"
#include "../model/search/text_finder.h"
#include "../model/search/image_finder.h"
#include "../model/search/sound_finder.h"
#include "../model/descriptor/text_descriptor_generator.h"
#include "../model/descriptor/image_descriptor_generator.h"
#include "../model/descriptor/sound_descriptor_generator.h"
#include "../model/descriptor/descriptor_generator.h"
#include "../view/console_IO.h"

int login(char* password);
char** search_data(char* file_path);
char** search_by_keywords(char** keywords);
int update_text_descriptor(int force);
int update_image_descriptor(int force);
int update_sound_descriptor(int force);

#endif /* GUI_FUNCTIONS_H_ */
