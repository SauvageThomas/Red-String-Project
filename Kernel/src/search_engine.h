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

#include "Data/constant.h"
#include "Tools/data_handler.h"

void launch_search_engine(Config config);
void init_search_engine(Config config);
void run_search_engine();
void close_search_engine();
void check_text_descriptor(char* path, Directory dir);
void check_image_descriptor(char* path, Directory dir, int n);
void check_sound_descriptor(char* path, Directory dir);

#endif
