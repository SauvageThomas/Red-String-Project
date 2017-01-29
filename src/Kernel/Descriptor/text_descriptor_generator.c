
#include "text_descriptor_generator.h"

Descriptor generate_text_descriptor(DataFile df){
	int matrix_length = 0;
	Descriptor descriptor = init_descriptor(df.path);
	char* content = read_string_from_file(df);
	char* new_content = remove_xml(content);
	remove_punctuation(new_content);
	char** words = remove_words(new_content, &matrix_length);

	descriptor.nb_maps = 1;
	descriptor.size = strlen(new_content);
	for (int i = 0; i < matrix_length; i++) {
		add_value_MapOfMap(&(descriptor.map), "0", words[i], 1);
	}
	return descriptor;
}


void generate_text_descriptors(DataFile df, Directory dir){
	puts(" -> Updating text descriptor...");
	write_string_in_file(df, ""); //Reset the file
	puts("file reset");
	for (int i = 0; i < dir.txt_size; i += 1) {
		Descriptor desc = generate_text_descriptor(dir.txt_files[i]);
		descriptor_to_file(desc, df);
		if (DEBUG)
			printf("[%d] Text descriptor updated : %s\n", (i+1), dir.txt_files[i].path);
	}
	printf(" -> Done ! %d text descriptors updated !\n", dir.txt_size);
}

void check_text_descriptor(char* path, Directory dir) {
	puts("\n\n ==================================================================");
	puts(" >>>    TEXT DESCRIPTOR UPDATE\n");
	char* full_path = strcat_path(path, "text_descriptors");
	DataFile df = init_data_file(full_path);
	if (DEBUG || check_descriptor(df, dir.txt_files, dir.txt_size)) {
		generate_text_descriptors(df, dir);
		update_index();
	}
}
