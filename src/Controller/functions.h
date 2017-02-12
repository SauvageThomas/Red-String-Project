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

#include "../Kernel/Data/constant.h"
#include "../Kernel/Data/config.h"
#include "../Kernel/Tools/report.h"
#include "../Kernel/Tools/data_handler.h"
#include "../Kernel/Search/data_manager.h"
#include "../Kernel/Search/text_finder.h"
#include "../Kernel/Search/image_finder.h"
#include "../Kernel/Search/sound_finder.h"
#include "../Kernel/Descriptor/text_descriptor_generator.h"
#include "../Kernel/Descriptor/image_descriptor_generator.h"
#include "../Kernel/Descriptor/sound_descriptor_generator.h"
#include "../Kernel/Descriptor/descriptor_generator.h"



void xor_crypt(char *password);
char* get_value_of(const char* value);
void load_config();
void wip();
void input_error(char *input);
int login();
void get_input(char* buffer);
void search_by_keyword(char *path);
void search_by_file();
void modif_config();
void clear_console();
void display_data_base(char *path);
void error_config_file();
char *remove_path(char *in);
void generate_all_descriptors();
int update_text_descriptor(char* path, Directory dir);
int update_image_descriptor(char* path, Directory dir, int n);
int update_sound_descriptor(char* path, Directory dir, int k, int m);
time_t chrono();
void display_rank(char *file_name, int rank);

#if (defined(_WIN32) || defined(_WIN64))
#define OS 1
#else
#define OS 0
#endif

#endif /* GUI_FUNCTIONS_H_ */
