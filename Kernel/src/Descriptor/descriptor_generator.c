/*
 * descriptor_generator.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */ 	 

#include <dirent.h>
#include <stdio.h>
#include "descriptor_generator.h"

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
}
*/
