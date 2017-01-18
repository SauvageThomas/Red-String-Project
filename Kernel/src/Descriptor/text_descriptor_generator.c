#include "descriptor_generator.h"
#include "../Search/text_finder.h"

Descriptor generate_text_descriptor(DataFile df){
	int matrix_length = 0;
	Descriptor descriptor = init_descriptor(df.path);
	
	char* content = read_string_from_file(df);
	char* new_content = remove_xml(content);
	remove_punctuation(new_content);
	char** words = remove_words(new_content, &matrix_length);


	descriptor.size = strlen(new_content);
	for (int i = 0; i < matrix_length; i++) {
		add_value_hash_map(&(descriptor.map), words[i]);
	}
	return descriptor;
}


void generate_text_descriptors(DataFile df, Directory dir){
	puts(" -> Updating text descriptor...");
	write_string_in_file(df, ""); //Reset the file
	for (int i = 0; i < dir.txt_size; i += 1) {
		Descriptor desc = generate_text_descriptor(dir.txt_files[i]);
		descriptor_to_file(desc, df);
		if (DEBUG)
			printf("[%d] Text descriptor updated : %s\n", (i+1), dir.txt_files[i].path);
	}
	printf(" -> Done ! %d text descriptors updated !\n", dir.txt_size);
}
