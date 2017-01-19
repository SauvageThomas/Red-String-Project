#include "sound_descriptor_generator.h"

Descriptor generate_sound_descriptor(DataFile df, int size_window, int nb_intervalles){
	Descriptor descriptor = init_descriptor(df.path);
	size_t count_maps;
	puts("OK");
	descriptor.map = file_content(df, size_window, nb_intervalles, &count_maps);
	puts("OK");
	descriptor.size = df.length;
	descriptor.nb_maps = count_maps;
	return descriptor;
}

void generate_sound_descriptors(DataFile df, Directory dir, int size_window, int nb_intervalles){
	puts(" -> Updating sound descriptor...");
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < dir.audio_size; i += 1) {
		printf("name : %s\n", dir.audio_files[i].path);
		Descriptor desc = generate_sound_descriptor(dir.audio_files[i], size_window, nb_intervalles);
		descriptor_to_file(desc, df);
		//printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.audio_files[i].path);
	}
}
