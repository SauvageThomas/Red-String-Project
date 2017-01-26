
#include "sound_descriptor_generator.h"

Descriptor generate_sound_descriptor(DataFile df, int size_window, int nb_intervalles){
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

void generate_sound_descriptors(DataFile df, Directory dir, int size_window, int nb_intervalles){
	puts(" -> Updating sound descriptor...");
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < dir.audio_size; i += 1) {
		printf("name : %s\n", dir.audio_files[i].path);
		Descriptor desc = generate_sound_descriptor(dir.audio_files[i], size_window, nb_intervalles);
		descriptor_to_file(desc, df);
		printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.audio_files[i].path);
	}
}
