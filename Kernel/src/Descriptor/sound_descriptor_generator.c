#include "../Tools/data_handler.h"
#include "descriptor_generator.h"
#include "../Data/constant.h"

Descriptor generate_sound_descriptor(DataFile df){
	Descriptor descriptor = init_descriptor(df.path);
	return descriptor;
}

void generate_sound_descriptors(DataFile df, Directory dir){
	write_string_in_file(df, ""); //Reset the file
	puts("Audio files");
	for (int i = 0; i < dir.audio_size; i += 1) {
		Descriptor desc = generate_sound_descriptor(dir.audio_files[i]);
		descriptor_to_file(desc, df);
		//printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.audio_files[i].path);
	}
}
