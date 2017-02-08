/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */


#ifndef DESCRIPTOR_DATA_MANAGER_H_
#define DESCRIPTOR_DATA_MANAGER_H_

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include "text_finder.h"
#include "image_finder.h"
#include "sound_finder.h"
#include "../Tools/report.h"
#include "../../Controller/functions.h"
#include "../Data/constant.h"
#include "../Tools/data_handler.h"
#include "../Descriptor/descriptor_generator.h"
enum FileType {
	TEXT, IMAGE, SOUND
};

int search_data(Config config, char* file_path);
Directory get_all_files(char *path);
char *pretty_print_string(char *in);
char *pretty_print_image(char *in);
char *pretty_print_sound(char *in);

#endif
