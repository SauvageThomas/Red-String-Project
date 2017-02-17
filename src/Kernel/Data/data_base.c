
#include "data_base.h"

typedef struct {
	DataFile* txt_files;
	size_t txt_size;
	DataFile* audio_files;
	size_t audio_size;
	DataFile* image_files;
	size_t image_size;
} Directory;

Directory DATA_BASE = {NULL, -1, NULL, -1, NULL, -1};


DataFile* get_text_files(){
	return DATA_BASE.txt_files;
}

DataFile* get_image_files(){
	return DATA_BASE.image_files;
}

DataFile* get_sound_files(){
	return DATA_BASE.audio_files;
}

size_t get_nb_text(){
	return DATA_BASE.txt_size;
}

size_t get_nb_image(){
	return DATA_BASE.image_size;
}

size_t get_nb_sound(){
	return DATA_BASE.audio_size;
}

void free_data_base(){
	for (int i = 0; i < DATA_BASE.txt_size; i++){
		free_data_file(DATA_BASE.txt_files[i]);
	}
	free(DATA_BASE.txt_files);

	for (int i = 0; i < DATA_BASE.image_size; i++){
		free_data_file(DATA_BASE.image_files[i]);
	}
	free(DATA_BASE.image_files);

	for (int i = 0; i < DATA_BASE.audio_size; i++){
		free_data_file(DATA_BASE.audio_files[i]);
	}
	free(DATA_BASE.audio_files);
}

void load_data_base(char *path) {
	/*
	Return a Directory structure containing every informations about a directory and
	useful files
	*/
	size_t max_size_text = 15;
	size_t max_size_audio = 15;
	size_t max_size_image = 15;

	DATA_BASE.txt_size = 0;
	DATA_BASE.audio_size = 0;
	DATA_BASE.image_size = 0;

	DATA_BASE.txt_files = malloc(sizeof(DataFile) * max_size_text);
	DATA_BASE.audio_files = malloc(sizeof(DataFile) * max_size_audio);
	DATA_BASE.image_files = malloc(sizeof(DataFile) * max_size_image);

	char *full_path = malloc(KSIZE * 2);

	DIR *dp;
	struct dirent *ep;
	dp = opendir(path);

	if (dp != NULL) {
		while (ep = readdir(dp)) {
			strcpy(full_path, path);

			if (DATA_BASE.txt_size >= max_size_text - 1) {
				max_size_text *= 2;
				DATA_BASE.txt_files = realloc(DATA_BASE.txt_files, sizeof(DataFile) * max_size_text);
			}
			if (DATA_BASE.audio_size >= max_size_audio - 1) {
				max_size_audio *= 2;
				DATA_BASE.audio_files = realloc(DATA_BASE.audio_files, sizeof(DataFile) * max_size_audio);
			}
			if (DATA_BASE.image_size >= max_size_image - 1) {
				max_size_image *= 2;
				DATA_BASE.image_files = realloc(DATA_BASE.image_files, sizeof(DataFile) * max_size_image);
			}

			strcat(full_path, ep->d_name);
			
			enum FileType file_type = get_data_file_extension(ep->d_name);

			switch (file_type) {
			case TEXT:
				DATA_BASE.txt_files[DATA_BASE.txt_size] = init_data_file(full_path);
				DATA_BASE.txt_files[DATA_BASE.txt_size].type = malloc(strlen("text") + 1);
				strcpy(DATA_BASE.txt_files[DATA_BASE.txt_size].type, "text");
				DATA_BASE.txt_size += 1;
				break;
			case IMAGE:
				DATA_BASE.image_files[DATA_BASE.image_size] = init_data_file(full_path);
				DATA_BASE.image_files[DATA_BASE.image_size].type = malloc(strlen("image") + 1);
				strcpy(DATA_BASE.image_files[DATA_BASE.image_size].type, "image");
				DATA_BASE.image_size += 1;
				break;
			case SOUND:
				DATA_BASE.audio_files[DATA_BASE.audio_size] = init_data_file(full_path);
				DATA_BASE.audio_files[DATA_BASE.audio_size].type = malloc(strlen("audio") + 1);
				strcpy(DATA_BASE.audio_files[DATA_BASE.audio_size].type, "audio");
				DATA_BASE.audio_size += 1;
				break;
			default:
				break;
			}
		}
		(void) closedir(dp);
	} else {
		DATA_BASE.txt_size = -1;
	}
}