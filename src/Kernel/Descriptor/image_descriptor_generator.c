#include "image_descriptor_generator.h"

Descriptor generate_image_descriptor(DataFile df, int quant) {
	Descriptor descriptor = init_descriptor(df.path);
	size_t size;
	size_t *quant_array = quantify_file(quant, df, &size);
	char str[4];

	int new_size = size;
	descriptor.size = new_size;
	descriptor.nb_maps = 1;
	//printf("SIZE = %u\n", new_size);
	for (int i = 0; i < new_size; i += 1) {
		sprintf(str, "%u", quant_array[i]);
		//printf("[%d/%u] value = %s\n", i, new_size, str);
		add_value_MapOfMap(&(descriptor.map), "0", str, 1);
	}
	//puts("Free new_array");
	free(quant_array);
	return descriptor;
}

void generate_image_descriptors(DataFile df, Directory dir, int quant) {
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
	puts("\n\n ==================================================================");
	puts(" >>>    IMAGE DESCRIPTOR UPDATE\n");
	char* full_path = strcat_path(path, "image_descriptors");
	DataFile df = init_data_file(full_path);
	int updated = check_descriptor(df, dir.image_files, dir.image_size);
	if (DEBUG || updated) {
		generate_image_descriptors(df, dir, n);
	}
}
