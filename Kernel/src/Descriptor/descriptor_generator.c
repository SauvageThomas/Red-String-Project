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

int check_descriptor(char* path, char* file_name){
	char* full_path = malloc(KSIZE);
	sprintf(full_path, "%s%s", path, file_name);
	DataFile df = init_data_file(full_path);
	if (!is_existing_file(df)){
		//TODO: generate desc
		puts("no descriptor found !");
	}
	else{
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
	if (0){
		return EXIT_SUCCESS;
	}

	// For each file :
	/*
	DataFile test = init_data_file("res/FICHIER_PROJET/03-Mimer_un_signal_nerveux_pour.xml");
	char* words = generate_descriptor(test);
	printf("OK\n");
	write_string_in_file(df_text, words);
	printf("File descriptor SUCCESS : %s\n", test.path);
	*/
	
	return EXIT_FAILURE;

	//TODO: Complete the other cases
}


char* generate_descriptor(DataFile df){
	HashMap word_occurences;
	init_hash_map(&word_occurences);
	int matrix_length = 0;
	printf("GENERATE DESCRIPTOR :\n");

	//TODO: extract common method !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	char* content = read_string_from_file(df);
	content = remove_xml(content);
	content = remove_punctuation(content);
	char** words = remove_words(content, &matrix_length);

	
	for (int i=0; i<matrix_length; i++){
		add_value_hash_map(&word_occurences, words[i]);
	}

	char* result = malloc(1000);
	strcpy(result, "\n> ");
	strcat(result, df.path);
	strcat(result, "\n");
	while(word_occurences != NULL){
		strcat(result, pop_value_hash_map(&word_occurences));
	}
	return result;
	//TODO: create new file with same name + "descriptor" and print map in 
}