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

#include "../kernel/tools/data_handler.h"
#include "../kernel/data/constant.h"
#include "../kernel/data/config.h"
#include "../kernel/search/data_manager.h"
#include "../kernel/search/text_finder.h"
#include "../kernel/search/image_finder.h"
#include "../kernel/search/sound_finder.h"
#include "../kernel/descriptor/text_descriptor_generator.h"
#include "../kernel/descriptor/image_descriptor_generator.h"
#include "../kernel/descriptor/sound_descriptor_generator.h"
#include "../kernel/descriptor/descriptor_generator.h"


char** search_data(char* file_path);
char** search_by_keywords(char** keywords);
int update_text_descriptor(int force);
int update_image_descriptor(int force);
int update_sound_descriptor(int force);

#endif /* GUI_FUNCTIONS_H_ */
