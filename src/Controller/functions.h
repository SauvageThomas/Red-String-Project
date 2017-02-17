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
#include "../Kernel/Tools/report.h"
#include "../Kernel/Search/data_manager.h"
#include "../Kernel/Search/text_finder.h"
#include "../Kernel/Search/image_finder.h"
#include "../Kernel/Search/sound_finder.h"
#include "../Kernel/Descriptor/text_descriptor_generator.h"
#include "../Kernel/Descriptor/image_descriptor_generator.h"
#include "../Kernel/Descriptor/sound_descriptor_generator.h"
#include "../Kernel/Descriptor/descriptor_generator.h"


int search_data(char* file_path);
void input_error(char *input);
void get_input(char* buffer);
void search_by_keyword(char *path);
void modif_config();
void clear_console();
void error_config_file();
char *remove_path(char *in);
void generate_all_descriptors();

int update_text_descriptor(int force);
int update_image_descriptor(int force);
int update_sound_descriptor(int force);
time_t chrono();

#endif /* GUI_FUNCTIONS_H_ */
