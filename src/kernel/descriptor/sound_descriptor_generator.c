
#include "sound_descriptor_generator.h"

Descriptor generate_sound_descriptor(DataFile df, int size_window, int nb_intervalles){
	/*
	Generate the descriptor of the sound given in parameter along with the number of intervals
	and the size of each window
	*/
	Descriptor descriptor = init_descriptor(df.path);
	size_t len = strlen(df.path);
	char *tmp = df.path;
	df.path = malloc(KSIZE * 2 + 15);
	strcpy(df.path, tmp);

	df.path[len + 1] = '\0';
	df.path[len] = '2';
	df.path[len - 1] = 'n';
	df.path[len - 2] = 'i';
	df.path[len - 3] = 'b';
	size_t count_maps;
	int* sound_values = file_content(df, size_window, nb_intervalles, &count_maps);
	int key_map_of_map;
	int max = df.length/sizeof(double);
	descriptor.size = df.length;
	descriptor.nb_maps = count_maps;
	descriptor.nb_intervalles = nb_intervalles;
	char **array = malloc(descriptor.nb_maps* sizeof(char*));
	for (size_t i = 0; i < descriptor.nb_maps; i++) {
		array[i] = malloc(5*sizeof(char));
		sprintf(array[i], "%zu", i);
	}
	char **array2 = malloc(nb_intervalles* sizeof(char*));
	for (size_t i = 0; i < nb_intervalles; i++) {
		array2[i] = malloc(5*sizeof(char));
		sprintf(array2[i], "%zu", i);
	}
	for (int i = 0; i < max; i += 1) {
		key_map_of_map = (int)floor((i)/(double)size_window);
		add_value_MapOfMap(&(descriptor.map), array[key_map_of_map], array2[sound_values[i]], 1);
	}
	return descriptor;
}

void generate_sound_descriptors(DataFile df){
	/*
	Iterate over every file in the directory dir and call generate_sound_descriptor on every file
	with both the number of intervals and the size of each window.
	Write the descriptor in the file df
	*/
	size_t size_window = get_sizet_from_config("taille_des_fenetres");
	size_t nb_intervalles = get_sizet_from_config("nombre_de_barre");
	size_t nb_sound = get_nb_sound();
	DataFile* sound_files = get_sound_files();
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < nb_sound; i += 1) {
		Descriptor desc = generate_sound_descriptor(sound_files[i], size_window, nb_intervalles);
		descriptor_to_file(desc, df);
	}
}

int check_sound_descriptor(int force) {
	/*
	Check if the sound descriptor located at path is up-to-date according to the files in dir
	with both the number of intervals m and the size of each window k.
	*/
	char* path = get_data_from_config("descriptors");
	char* full_path = strcat_path(path, "sound_descriptors");
	DataFile df = init_data_file(full_path);
	if (DEBUG || force || check_descriptor(df, get_sound_files(), get_nb_sound())) {
		generate_sound_descriptors(df);
		return 1;
	}
	return 0;
}
