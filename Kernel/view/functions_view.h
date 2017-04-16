
#ifndef GUI_GUI_H_
#define GUI_GUI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../controller/functions.h"
#include "../model/data/constant.h"
#include "../model/data/config.h"
#include "../model/data/data_base.h"
#include "../model/tools/data_handler.h"
#include "console_IO.h"

void show_main_menu();	
void show_search_menu();
void show_config_menu();

#endif /* GUI_GUI_H_ */
