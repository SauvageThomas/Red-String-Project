#include "../Tools/data_handler.h"
#include "descriptor_generator.h"
#include "../Data/constant.h"

Descriptor generate_sound_descriptor(DataFile df, int size_window, int nb_intervalles){
	Descriptor descriptor = init_descriptor(df.path);
	descriptor.map = file_content(df, size_window, nb_intervalles);
	descriptor.size = df.length;
	return descriptor;
}

void generate_sound_descriptors(DataFile df, Directory dir, int size_window, int nb_intervalles){
	write_string_in_file(df, ""); //Reset the file
	puts("Audio files");
	for (int i = 0; i < dir.audio_size; i += 1) {
		Descriptor desc = generate_sound_descriptor(dir.audio_files[i], size_window, nb_intervalles);
		descriptor_to_file(desc, df);
		//printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.audio_files[i].path);
	}
}
