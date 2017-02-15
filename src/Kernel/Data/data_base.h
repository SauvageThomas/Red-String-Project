
#ifndef DATA_DATA_BASE_H_
#define DATA_DATA_BASE_H_

#include "../Tools/data_handler.h"
#include <dirent.h>



enum FileType {
	TEXT, IMAGE, SOUND
};

void load_data_base(char *path);
DataFile* get_text_files();
DataFile* get_image_files();
DataFile* get_sound_files();
size_t get_nb_text();
size_t get_nb_image();
size_t get_nb_sound();

#endif DATA_DATA_BASE_H_