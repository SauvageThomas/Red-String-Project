#include "image_descriptor_generator.h"

Descriptor generate_image_descriptor(DataFile df, int quant) {
	/*
	Generate the descpritor of the image given in parameter with the quantification quant
	*/
	Descriptor descriptor = init_descriptor(df.path);
	size_t size;
	size_t *quant_array = quantify_file(quant, df, &size);
	char str[4];

	int new_size = size;
	descriptor.size = new_size;
	descriptor.nb_maps = 1;
	for (int i = 0; i < new_size; i += 1) {
		sprintf(str, "%u", quant_array[i]);
		add_value_MapOfMap(&(descriptor.map), "0", str, 1);
	}

	free(quant_array);
	return descriptor;
}

void generate_image_descriptors(DataFile df, Directory dir, int quant) {
	/*
	Iterate over every file in the directory dir and call generate_image_descriptor on every file
	with the quantification quant
	Write the descriptor in the file df
	*/
	puts(" -> Updating image descriptor...");
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < dir.image_size; i += 1) {
		Descriptor desc = generate_image_descriptor(dir.image_files[i], quant);
		descriptor_to_file(desc, df);
		if(DEBUG)
			printf("[%d] Image descriptor updated : %s\n", (i+1), dir.image_files[i].path);
	}
}

void check_image_descriptor(char* path, Directory dir, int n) {
	/*
	Check if the image descriptor located at path is up-to-date according to the files in dir
	with the quantification n 
	*/
	puts("\n\n ==================================================================");
	puts(" >>>    IMAGE DESCRIPTOR UPDATE\n");
	char* full_path = strcat_path(path, "image_descriptors");
	DataFile df = init_data_file(full_path);
	int updated = check_descriptor(df, dir.image_files, dir.image_size);
	if (DEBUG || updated) {
		generate_image_descriptors(df, dir, n);
	}
}
