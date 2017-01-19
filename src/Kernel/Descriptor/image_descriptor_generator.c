#include <stdio.h>

#include "../Tools/data_handler.h"
#include "../Data/constant.h"
#include "descriptor_generator.h"

#include "../Search/image_finder.h"

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
