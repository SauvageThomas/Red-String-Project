
#ifndef GUI_GUI_H_
#define GUI_GUI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../controller/functions.h"
#include "../kernel/data/constant.h"
#include "../kernel/data/config.h"
#include "../kernel/data/data_base.h"
#include "../kernel/tools/data_handler.h"
#include "console_IO.h"

void show_main_menu();	
void show_search_menu();
void show_config_menu();

#endif /* GUI_GUI_H_ */
