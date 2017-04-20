
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


void generate_text_descriptors(DataFile df){
	/*
	Iterate over every files in dir and call generate_text_descriptor and save it in the file df
	*/
	DataFile* text_files = get_text_files();
	size_t nb_txt = get_nb_text();

	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < nb_txt; i += 1) {
		Descriptor desc = generate_text_descriptor(text_files[i]);
		descriptor_to_file(desc, df);
		
	}
}

int check_text_descriptor(int force) {
	/*
	Check if the text descriptor located at path is up-to-date according to the files in dir
	*/
	char* path = get_data_from_config("descriptors");
	char* desc_path = strcat_path(path, "text_descriptors");
	char* index_path = strcat_path(path, "text_index");
	DataFile df = init_data_file(desc_path);
	DataFile idx = init_data_file(index_path);

	if (DEBUG || force || check_descriptor(df, get_text_files(), get_nb_text())) {
		generate_text_descriptors(df);
		update_index(desc_path, index_path);
		return 2;
	}
	if (!is_existing_file(idx)){
		update_index(desc_path, index_path);
		return 1;
	}
	return 0;
}
