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
#include "../../controller/functions.h"
#include "../data/constant.h"
#include "../data/config.h"

char *pretty_print_string(char *in);
char *pretty_print_image(char *in);
char *pretty_print_sound(char *in);

#endif
