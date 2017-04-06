/*
 ============================================================================
 Name        : index_generator.c
 Author      : Pierre
 Version     :
 Description : Generate index file
 ============================================================================
 */

#include "index_generator.h"


void update_index(char *desc_path, char *index_path) {
	/*
	 * CREATE OR UPDATE THE INDEX FILE
	 */
	
	DataFile fileSource = init_data_file(desc_path);
	char* text = malloc(fileSource.length);
	text = read_string_from_file(fileSource);

	int intNumberOccurenceCurent;
	MapOfMap map;
	init_MapOfMap(&map);
	char* file_name = malloc(KSIZE);
	

	for (int i = 0; i < fileSource.length; i++) {
		if (text[i] == '>'){
			int cursor = 0;
			i++;
			while(text[i] != '\n'){
				file_name[cursor] = text[i];
				cursor++;
				i++;
			}
			file_name[cursor] = '\0';
		}
		if (text[i] != ' ' && text[i] != '\n' && text[i] != '>'){
			int cursor = 0;
			char* word = malloc(KSIZE);
			char* nb_occurences = malloc(3); // <= 999
			cursor = 0;
			while(text[i] != ' '){
				word[cursor] = text[i];
				cursor++;
				i++;
			}
			word[cursor] = '\0';
			i++;
			cursor = 0;
			while(text[i] != '\n'){
				nb_occurences[cursor] = text[i];
				cursor++;
				i++;
			}
			nb_occurences[cursor] = '\0';
			sscanf(nb_occurences, "%d", &intNumberOccurenceCurent);
			add_value_MapOfMap(&map, word, file_name, intNumberOccurenceCurent);
		}		
	}
	DataFile df = init_data_file(index_path);
	write_string_in_file(df, ""); //reset the file
	while (map != NULL) {
		append_string_in_file(df, pop_value_MapOfMap(&map));
	}
	free(file_name);
}

