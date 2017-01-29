
/*
 ============================================================================
 Name        : search_engine.h
 Author      : Kévin
 Version     :
 Description : Search Engine
 ============================================================================
 */

#ifndef SEARCH_ENGINE_H_
#define SEARCH_ENGINE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Kernel/Descriptor/descriptor_generator.h"
#include "../Controller/functions.h"
#include "../Kernel/Descriptor/text_descriptor_generator.h"
#include "../Kernel/Descriptor/image_descriptor_generator.h"
#include "../Kernel/Descriptor/sound_descriptor_generator.h"
#include "../Kernel/Search/data_manager.h"
#include "../Kernel/Tools/report.h"
#include "../Kernel/Tools/data_handler.h"
#include "../Console/gui.h"
#include "../Kernel/Data/constant.h"


void launch_search_engine(Config config);
void init_search_engine(Config config);
void run_search_engine();
void close_search_engine();

#endif
