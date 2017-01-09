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

int check_descriptors(char* path) {
	puts("DESCRIPTOR CHECK \n");

	char text_path[KSIZE];
	char audio_path[KSIZE];
	char video_path[KSIZE];

	strcpy(text_path, path);
	strcpy(audio_path, path);
	strcpy(video_path, path);

	strcat(text_path, "text_descriptors");
	strcat(audio_path, "audio_descriptors");
	strcat(video_path, "video_descriptors");

	DataFile df_text = init_data_file(text_path);
	DataFile df_audio = init_data_file(audio_path);
	DataFile df_video = init_data_file(video_path);


	if (is_existing_file(df_text) && is_existing_file(df_audio) && is_existing_file(df_video))
		return EXIT_SUCCESS;
	
	return EXIT_FAILURE;

	//TODO: Complete the other cases
}

/*
void generate_descriptor(TextFile tf){
	HashMap word_occurences;
	init_hash_map(word_occurences);

	for (i=0; i<tf.nb_word; i++){
		add_value_hash_map(&word_occurences, tf.words[i]);
	}

	print_hash_map(word_occurences);

	//TODO: create new file with same name + "descriptor" and print map in 
}*/