
#include "text_descriptor_generator.h"

Descriptor generate_text_descriptor(DataFile df){
	/*
	Generate the descriptor of the file df
	*/
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
	/*
	Iterate over every files in dir and call generate_text_descriptor and save it in the file df
	*/
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
	/*
	Check if the text descriptor located at path is up-to-date according to the files in dir
	*/
	puts("\n\n ==================================================================");
	puts(" >>>    TEXT DESCRIPTOR UPDATE\n");
	char* desc_path = strcat_path(path, "text_descriptors");
	char* index_path = strcat_path(path, "text_index");
	DataFile df = init_data_file(desc_path);
	DataFile idx = init_data_file(index_path);
	if (DEBUG || check_descriptor(df, dir.txt_files, dir.txt_size)) {
		generate_text_descriptors(df, dir);
		update_index(desc_path, index_path);
	}
	else if (!is_existing_file(idx)){
		update_index(desc_path, index_path);
	}
}
