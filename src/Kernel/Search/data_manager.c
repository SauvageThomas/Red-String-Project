/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016	
 *      Author: THOMAS
 */

#include "data_manager.h"

int search_data(Config config, char* file_path) {
	DataFile df = init_data_file(file_path);
	HashMap result = NULL;

	if (!is_existing_file(df)) {
		return FILE_NOT_FOUND;
	}

	if (is_empty_file(df)) {
		return EMPTY;
	}

	enum FileType file_type = get_data_file_extension(df.path);

	//Directory dir = get_all_files(get_value_of(config, "path"));

	char full_path[KSIZE * 2];
	strcpy(full_path, get_value_of(config, "descriptors"));

	switch (file_type) {
	case TEXT:
		strcat(full_path, "text_descriptors");
		break;
	case IMAGE:
		strcat(full_path, "image_descriptors");
		//puts("hey");
		//find_image(get_value_of(config, "quantification"), df);
		break;
	case SOUND:
		strcat(full_path, "sound_descriptors");
		//find_sound(df, get_value_of(config, "taille_des_fenetres"), get_value_of(config, "nombre_de_barre"));
		break;

	default:
		return FILE_TYPE_NOT_SUPPORTED;
		break;
	}

	df = init_data_file(full_path);

	char *content = read_string_from_file(df);
	int size_desc;
	Descriptor *desc = extract_all_descriptor(content, &size_desc);
	int cpt = 0;

	while (strcmp(desc[cpt].file_name, file_path)) {
		//printf("%s and %s\n", desc[cpt].file_name, file_path);
		cpt += 1;
	}

	puts("\n\nFichiers équivalents :\n");
	Descriptor descriptor = desc[cpt];
	//printf("%d\n", cpt);
	int i;
	for (i = 0; i < size_desc; i += 1) {
		//printf("%d\n", i);
		if (i != cpt) {
			int common = compare_descriptors(descriptor, desc[i]);
			add_nb_value_hash_map(&result, desc[i].file_name, common);
			printf("%s => %d\n",desc[i].file_name, common);
		}
		//exit(0);

	}
	int max = 5;
	if (i < max) {
		max = i;
	}

	for (int i = 0; i < max; i += 1) {
		char *tmp = pop_value_hash_map(&result);

		//Change the content of the string
		char *final_string;
		switch (file_type) {
		case TEXT:
			final_string = pretty_print_string(tmp);
			break;
		case IMAGE:
			final_string = pretty_print_image(tmp);
			break;
		case SOUND:
			final_string = pretty_print_sound(tmp);
			break;
		}

		printf("%s\n", final_string);
	}
	return SUCCESS;
}

char *pretty_print_string(char *in) {
	char *out = malloc(KSIZE + 15);
	out[0] = '\0';

	char c = in[0];
	int j = 0;
	while (c != '\0') {
		c = in[j];
		strncat(out, &c, 1);
		if (c == '/') {
			out[0] = '\0';
		} else if (c == ' ') {
			strcat(out, "=> ");
		}
		j += 1;
	}
	return out;
}

char *pretty_print_image(char *in) {
	char *out = malloc(KSIZE + 15);
	out[0] = '\0';

	char c = in[0];
	int j = 0;
	while (c != '\0') {
		c = in[j];
		strncat(out, &c, 1);
		if (c == '/') {
			out[0] = '\0';
		} else if (c == ' ') {
			return out;
		}
		j += 1;
	}
	return NULL;
}

char *pretty_print_sound(char *in) {
	return NULL;
}

Directory get_all_files(char *path) {
	size_t max_size_text = 15;
	size_t max_size_audio = 15;
	size_t max_size_image = 15;

	Directory dir;

	dir.txt_size = 0;
	dir.audio_size = 0;
	dir.image_size = 0;

	dir.txt_files = malloc(sizeof(DataFile) * max_size_text);
	dir.audio_files = malloc(sizeof(DataFile) * max_size_audio);
	dir.image_files = malloc(sizeof(DataFile) * max_size_image);

	char *full_path = malloc(KSIZE * 2);

	DIR *dp;
	struct dirent *ep;
	dp = opendir(path);

	if (dp != NULL) {
		while (ep = readdir(dp)) {
			strcpy(full_path, path);

			if (dir.txt_size >= max_size_text - 1) {
				max_size_text *= 2;
				dir.txt_files = realloc(dir.txt_files,
						sizeof(DataFile) * max_size_text);
			}
			if (dir.audio_size >= max_size_audio - 1) {
				max_size_audio *= 2;
				dir.audio_files = realloc(dir.audio_files,
						sizeof(DataFile) * max_size_audio);
			}
			if (dir.image_size >= max_size_image - 1) {
				max_size_image *= 2;
				dir.image_files = realloc(dir.image_files,
						sizeof(DataFile) * max_size_image);
			}

			strcat(full_path, ep->d_name);
			if (DEBUG) {
				printf("text %d audio %d image %d\n", dir.txt_size,
						dir.audio_size, dir.image_size);/*
						 printf("text %d audio %d image %d\n", max_size_text,
						 max_size_audio, max_size_image);*/
			}
			//puts(ep->d_name);

			enum FileType file_type = get_data_file_extension(ep->d_name);

			switch (file_type) {
			case TEXT:
				dir.txt_files[dir.txt_size] = init_data_file(full_path);
				dir.txt_files[dir.txt_size].type = malloc(strlen("text") + 1);
				strcpy(dir.txt_files[dir.txt_size].type, "text");
				dir.txt_size += 1;
				break;
			case IMAGE:
				dir.image_files[dir.image_size] = init_data_file(full_path);
				dir.image_files[dir.image_size].type = malloc(
						strlen("image") + 1);
				strcpy(dir.image_files[dir.image_size].type, "image");
				dir.image_size += 1;
				break;
			case SOUND:
				dir.audio_files[dir.audio_size] = init_data_file(full_path);
				dir.audio_files[dir.audio_size].type = malloc(
						strlen("audio") + 1);
				strcpy(dir.audio_files[dir.audio_size].type, "audio");
				dir.audio_size += 1;
				break;
			default:
				break;
			}
		}
		(void) closedir(dp);
	} else {
		dir.txt_size = -1;
	}
	return dir;

}
