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
#include "../Kernel/Tools/report.h"
#include "../Kernel/Tools/data_handler.h"
#include "../Kernel/Search/data_manager.h"
#include "../Kernel/Search/text_finder.h"
#include "../Kernel/Search/image_finder.h"
#include "../Kernel/Search/sound_finder.h"

void xor_crypt(char *password);
char* get_value_of(Config config, const char* value);
Config load_config();
void wip();
void input_error(char *input);
int login();
void get_input(char* buffer);
void search_by_keyword();
void search_by_file();
void modif_config();
void clear_console();

#endif /* GUI_FUNCTIONS_H_ */
