/*
 * descriptor_generator.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "descriptor_generator.h"
#include "../Search/data_manager.h"
#include "../Data/constant.h"
#include "../Tools/data_handler.h"
#include "../Tools/hash_map.h"
#include "../Search/text_finder.h"

/*
 int check_descriptors(){
 int updated = 0;
 puts("DESCRIPTOR CHECK :\n");
 DIR* text_directory = opendir("../res/FICHIER_PROJET/Textes/");
 if (text_directory == NULL)
 exit(1);
 //TODO: for each xml file :
 // 	check if descriptor exists
 // 	if no :
 //		DataFile df = init_data_file(path);
 //		TextFile tf = init_text_file(df);
 //		generate_descriptor(tf);
 //		updated = 1;
 return updated;
 */

int check_descriptor(char* path, char* file_name) {
	char* full_path = malloc(KSIZE);

	sprintf(full_path, "%s%s", path, file_name);

	DataFile df = init_data_file(full_path);

	if (df.length == 0) {
		//TODO: generate desc
		puts("no descriptor found !");
	} else {
		//TODO: check every file last modification date
		puts("Have to check every file...");
	}
	return 1;
}

int check_descriptors(char* path) {
	puts("CHECKING DESCRIPTORS...\n");

	check_descriptor(path, "text_descriptors");
	check_descriptor(path, "image_descriptors");
	check_descriptor(path, "sound_descriptors");

	// condition with res value
	if (0) {
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;

	//TODO: Complete the other cases
}

void generate_descriptors(char *desc_path, char *files_path) {

	char *full_path = malloc(KSIZE * 2);
	strcpy(full_path, desc_path);
	strcat(full_path, "text_descriptors");

	DataFile text_file = init_data_file(full_path);
	write_string_in_file(text_file, ""); //Reset the file

	Directory dir = get_all_files(files_path);
	//puts("begin");

	Descriptor text_descriptors[dir.txt_size];
	for (int i = 0; i < dir.txt_size; i += 1) {
		//printf("%d\n", i);
		Descriptor desc = generate_descriptor(dir.txt_files[i]);


		text_descriptors[i] = desc;

		descriptor_to_file(text_descriptors[i], text_file);
		printf("File descriptor SUCCESS : %s\n", dir.txt_files[i].path);

	}
	//free(dir.txt_files);
	/*
	 DataFile text_files[2];
	 text_files[0] = init_data_file(
	 "res/FICHIER_PROJET/03-Mimer_un_signal_nerveux_pour.xml");
	 text_files[1] = init_data_file("res/FICHIER_PROJET/1.xml");

	 for (int i = 0; i < 2; i += 1) {
	 Descriptor desc = generate_descriptor(text_files[i]);
	 text_descriptors[i] = desc;
	 descriptor_to_file(text_descriptors[i], text_file);
	 printf("File descriptor SUCCESS : %s\n", text_files[i].path);
	 }*/

	printf("OK\n");

}

Descriptor generate_descriptor(DataFile df) {
	//puts("meud ? !");
	int matrix_length = 0;

	time_t rawtime;
	time(&rawtime);

	char* content = read_string_from_file(df);

	char *new_content = remove_xml(content);
	//free(content);
	//content = NULL;
	//printf("------------------------%s\n==", new_content);

	remove_punctuation(new_content);
	//printf("------------------------%s\n", content);
	//puts("begin");
	char** words = remove_words(new_content, &matrix_length);
	//puts("end");

	Descriptor descriptor = { .map = NULL, .file_name = df.path, .time =
			localtime(&rawtime), .size = strlen(new_content) };

	for (int i = 0; i < matrix_length; i++) {
		//printf("%s\n", words[i]);
		add_value_hash_map(&(descriptor.map), words[i]);
	}
	//printf("Date : %s\n", asctime(descriptor.time));

	//printf("GENERATE DESCRIPTOR :\n");
	//puts("end");

	//puts("Free double array");
	for (int i = 0; i < matrix_length; i += 1) {
		//free(words[i]);
	}
	//puts("Free Second double array");
	//free(words);
	//words = NULL;
	return descriptor;
}

//Appends the descriptor at the end of the file
void descriptor_to_file(Descriptor descriptor, DataFile df) {

	char* result = malloc(descriptor.size);
	strcpy(result, ">");
	strcat(result, descriptor.file_name);
	strcat(result, "?");
	strcat(result, asctime(descriptor.time));

	while (descriptor.map != NULL) {
		strcat(result, pop_value_hash_map(&(descriptor.map)));
	}

	append_string_in_file(df, result);

	//puts("Free desc2file");
	free(result);
	result = NULL;
}

