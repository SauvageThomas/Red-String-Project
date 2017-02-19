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

#include "../Kernel/Tools/data_handler.h"
#include "../Kernel/Data/constant.h"
#include "../Kernel/Data/config.h"
#include "../Kernel/Search/data_manager.h"
#include "../Kernel/Search/text_finder.h"
#include "../Kernel/Search/image_finder.h"
#include "../Kernel/Search/sound_finder.h"
#include "../Kernel/Descriptor/text_descriptor_generator.h"
#include "../Kernel/Descriptor/image_descriptor_generator.h"
#include "../Kernel/Descriptor/sound_descriptor_generator.h"
#include "../Kernel/Descriptor/descriptor_generator.h"


char** search_data(char* file_path);
char** search_by_keywords(char** keywords);
int update_text_descriptor(int force);
int update_image_descriptor(int force);
int update_sound_descriptor(int force);

#endif /* GUI_FUNCTIONS_H_ */
