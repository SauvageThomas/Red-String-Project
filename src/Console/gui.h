/*
 * gui.h
 *
 *  Created on: 6 janv. 2017
 *      Author: Thomas
 */

#ifndef GUI_GUI_H_
#define GUI_GUI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../Controller/functions.h"
#include "../Kernel/search_engine.h"
#include "../Kernel/Data/constant.h"
#include "../Kernel/Tools/data_handler.h"

void start_gui();
void search_gui();
void config_gui();

#endif /* GUI_GUI_H_ */
