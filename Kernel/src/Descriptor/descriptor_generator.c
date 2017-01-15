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
#include "../Search/image_finder.h"

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

	//For test purpose only return false
	return EXIT_FAILURE;

	//TODO: Complete the other cases
}

void generate_descriptors(char *desc_path, char *files_path, int quant) {

	char *full_path = malloc(KSIZE * 2);

	strcpy(full_path, desc_path);
	strcat(full_path, "text_descriptors");
	DataFile text_file = init_data_file(full_path);
	write_string_in_file(text_file, ""); //Reset the file

	strcpy(full_path, desc_path);
	strcat(full_path, "audio_descriptors");
	DataFile audio_file = init_data_file(full_path);
	write_string_in_file(audio_file, ""); //Reset the file

	strcpy(full_path, desc_path);
	strcat(full_path, "image_descriptors");
	DataFile image_file = init_data_file(full_path);
	write_string_in_file(image_file, ""); //Reset the file

	Directory dir = get_all_files(files_path);
	//puts("begin");

	puts("Text files");
	for (int i = 0; i < dir.txt_size; i += 1) {
		//printf("%d\n", i);
		Descriptor desc = generate_descriptor(dir.txt_files[i], 0);
		descriptor_to_file(desc, text_file);
		printf("File descriptor SUCCESS : %s\n", dir.txt_files[i].path);

	}
	//free(dir.txt_files);

	puts("Audio files");
	for (int i = 0; i < dir.audio_size; i += 1) {
		Descriptor desc = generate_descriptor(dir.audio_files[i], 0);
		descriptor_to_file(desc, audio_file);
		printf("File descriptor SUCCESS : %s\n", dir.audio_files[i].path);
	}

	puts("Image files");
	for (int i = 0; i < dir.image_size; i += 1) {
		Descriptor desc = generate_descriptor(dir.image_files[i], quant);
		descriptor_to_file(desc, image_file);
		printf("File descriptor SUCCESS : %s\n", dir.image_files[i].path);
	}

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

Descriptor generate_descriptor(DataFile df, int quant) {
	//puts("Generating descriptor ...");
	int matrix_length = 0;

	time_t rawtime;
	time(&rawtime);

	Descriptor descriptor = { .map = NULL, .file_name = df.path, .time =
			localtime(&rawtime) };

	//printf("Type : %s\n", df.type);
	if (!strcmp(df.type, "text")) {
		char* content = read_string_from_file(df);

		char *new_content = remove_xml(content);
		//content = realloc(content, 2);
		//free(content);
		//content = NULL;
		//printf("------------------------%s\n==", new_content);

		remove_punctuation(new_content);
		//printf("------------------------%s\n", content);
		//puts("begin");
		char** words = remove_words(new_content, &matrix_length);
		//puts("end");

		descriptor.size = strlen(new_content);
		for (int i = 0; i < matrix_length; i++) {
			//printf("%s\n", words[i]);
			add_value_hash_map(&(descriptor.map), words[i]);
		}
	} else if (!strcmp(df.type, "audio")) {

	} else if (!strcmp(df.type, "image")) {

		size_t size;
		size_t *quant_array = quantify_file(quant, df, &size);

		int max = size;
		size_t *new_array = malloc(max * sizeof(size_t));
		for (int i = 0; i < max; i += 1) {
			int tmp = quant_array[i];
			new_array[i] = tmp;
		}
		free(quant_array);

		char str[4];
		printf("%d\n", size);

		for (int i = 0; i < max; i += 1) {
			//printf("%d\n", quant_array[i]);
			sprintf(str, "%u", new_array[i]);
			if (new_array[i] > 99999) {
				//puts("waaat");
			}

			//If you uncomment it the overflow happens here
			//printf("%d -- %u/%u | %u => %s\n", max, i, max, new_array[i],	str);
			add_value_hash_map(&(descriptor.map), str);
			///puts("ok");
		}
		//puts("Free new_array");
		free(new_array);

	} else {
		fprintf(stderr, "Type : %s %s\n", df.type, strerror(errno));
		perror("WTF !");
	}

	//printf("Date : %s\n", asctime(descriptor.time));

	//printf("GENERATE DESCRIPTOR :\n");
	//puts("end");

	//puts("Free double array");
	/*for (int i = 0; i < matrix_length; i += 1) {
	 //free(words[i]);
	 words[i] = realloc(words[i], 2);
	 }
	 //puts("Free Second double array");
	 //free(words);
	 words = realloc(words, 2);*/
	//words = NULL;
	//puts("Done !");
	return descriptor;
}

//Appends the descriptor at the end of the file
void descriptor_to_file(Descriptor descriptor, DataFile df) {
	//puts("Desc to file");
	if (descriptor.map == NULL) {
		return;
	}
	//puts("Saving the descriptor ...");

	char *result = malloc(descriptor.size);
	if (result == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}
	strcpy(result, ">");
	strcat(result, descriptor.file_name);
	strcat(result, "?");
	strcat(result, asctime(descriptor.time));

	while (descriptor.map != NULL) {
		char *tmp = pop_value_hash_map(&(descriptor.map));
		//printf("Loop : %s", tmp);
		strcat(result, tmp);
		//puts("Free in d2f");
		//free(tmp);
	}
	//printf("%s\n", result);
	append_string_in_file(df, result);

	free_map(descriptor.map);
	//puts("Free desc2file");
	//free(&(descriptor.map));
	free(result);
	result = NULL;
	//puts("Done !");
}

