
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

void generate_image_descriptors(DataFile df) {
	/*
	Iterate over every file in the directory dir and call generate_image_descriptor on every file
	with the quantification quant
	Write the descriptor in the file df
	*/
	size_t quantification = get_sizet_from_config("quantification");
	DataFile* image_files = get_image_files();
	size_t nb_image = get_nb_image();
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < nb_image; i += 1) {
		descriptor_to_file(generate_image_descriptor(image_files[i], quantification), df);
	}
}

int check_image_descriptor(int force) {
	/*
	Check if the image descriptor located at path is up-to-date according to the files in dir
	with the quantification n
	*/
	char* path = get_data_from_config("descriptors");
	char* full_path = strcat_path(path, "image_descriptors");
	char* index_path = strcat_path(path, "image_index");
	DataFile df = init_data_file(full_path);
	DataFile idx = init_data_file(index_path);
	if (DEBUG || force || check_descriptor(df, get_image_files(), get_nb_image())) {
		generate_image_descriptors(df);
		update_index_image(path, index_path);
		return 2;
	}
	if (!is_existing_file(idx)){
		update_index_image(path, index_path);
		return 1;
	}
	return 0;
}
