#include "../Tools/data_handler.h"
#include "descriptor_generator.h"
#include "../Data/constant.h"
#include "../Search/sound_finder.h"

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
	char str[5];
	char str2[5];
	int max = df.length/sizeof(double);
	for (int i = 0; i < max; i += 1) {
		sprintf(str, "%d", sound_values[i]);
		key_map_of_map = (int)floor((i+1)/(double)size_window);
		sprintf(str2, "%d", key_map_of_map);
		printf("%s\n", str2);
		add_value_MapOfMap(&(descriptor.map), str2, str, 1);
	}
	printf("AAAAAAAAAAAAAAAA\n");
	printf("%s\n", pop_value_MapOfMap(&(descriptor.map)));
	printf("AAAAAAAAAAAAAAAA\n");
	printf("%s\n", pop_value_MapOfMap(&(descriptor.map)));
	descriptor.size = df.length;
	descriptor.nb_maps = count_maps;
	return descriptor;
}

void generate_sound_descriptors(DataFile df, Directory dir, int size_window, int nb_intervalles){
	puts(" -> Updating sound descriptor...");
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < dir.audio_size; i += 1) {
		Descriptor desc = generate_sound_descriptor(dir.audio_files[i], size_window, nb_intervalles);
		descriptor_to_file(desc, df);
		//printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.audio_files[i].path);
	}
}
