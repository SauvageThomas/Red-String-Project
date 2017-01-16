#include ".../Tools/data_handler.h"

Descriptor generate_image_descriptor(DataFile df, int quant){
	Descriptor descriptor = init_descriptor(df.path);
	size_t size;
	size_t *quant_array = quantify_file(quant, df, &size);
	char str[4];
	printf("SIZE = %d\n", size);
	
	descriptor.size = size;
	for (int i = 0; i < size ; i += 1) {
		sprintf(str, "%u", quant_array[i]);
		add_value_hash_map(&(descriptor.map), str);
	}
	puts("Free new_array");
	free(quant_array);
	return descriptor;
}

void generate_image_descriptors(DataFile df, Directory dir, int quant){
	write_string_in_file(df, ""); //Reset the file
	puts("Image files");
	for (int i = 0; i < dir.image_size; i += 1) {
		Descriptor desc = generate_image_descriptor(dir.image_files[i], quant);
		descriptor_to_file(desc, df);
		printf("[%d] File descriptor SUCCESS : %s\n", (i+1), dir.image_files[i].path);
	}
}