
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

#include "Descriptor/descriptor_generator.h"
#include "../Controller/functions.h"
#include "Descriptor/text_descriptor_generator.h"
#include "Descriptor/image_descriptor_generator.h"
#include "Descriptor/sound_descriptor_generator.h"
#include "Descriptor/index_generator.h"
#include "Search/data_manager.h"
#include "Tools/report.h"
#include "Tools/data_handler.h"
#include "../Console/gui.h"
#include "Data/constant.h"

void launch_search_engine(Config config);
void init_search_engine(Config config);
void run_search_engine();
void close_search_engine();
void check_text_descriptor(char* path, Directory dir);
void check_image_descriptor(char* path, Directory dir, int n);
void check_sound_descriptor(char* path, Directory dir, int k, int m);

#endif
