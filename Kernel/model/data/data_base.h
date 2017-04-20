
#ifndef DATA_DATA_BASE_H_
#define DATA_DATA_BASE_H_

#include "../tools/data_handler.h"
#include "config.h"
#include <dirent.h>

enum FileType {
	TEXT, IMAGE, SOUND
};

typedef struct {
	DataFile* txt_files;
	size_t txt_size;
	DataFile* audio_files;
	size_t audio_size;
	DataFile* image_files;
	size_t image_size;
} Directory;

void load_data_base();
DataFile* get_text_files();
DataFile* get_image_files();
DataFile* get_sound_files();
size_t get_nb_text();
size_t get_nb_image();
size_t get_nb_sound();
void free_data_base();

#endif DATA_DATA_BASE_H_
