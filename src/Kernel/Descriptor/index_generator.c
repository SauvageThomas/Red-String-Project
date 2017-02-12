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
	DataFile df = init_data_file(index_path);
	write_string_in_file(df, ""); //reset the file
	DataFile fileSource = init_data_file(desc_path);
	char* text = read_string_from_file(fileSource);

	char* fileName = malloc(KSIZE + 1);
	char* wordCurent = malloc(KSIZEWORD);
	char* numberOccurenceCurent = malloc(sizeof(int));
	int intNumberOccurenceCurent;
	int isFileName = 0;
	int isText = 0;
	int isWordCurent = 0;
	int isNumberOccurenceCurent = 0;
	char* pattern = "%c";
	MapOfMap map;
	init_MapOfMap(&map);
	int test = 0;
	char* tmp;

	for (int i = 0; i < fileSource.length; i++) {
		if (text[i] == '>') {
			test++;
			fileName = "";
			fileName = malloc(KSIZE + 1);
			isWordCurent = 0;
			isFileName = 1;
			continue;
		}
		if (isFileName == 1 && text[i] != '\n') {
			tmp = malloc(sizeof(char));
			sprintf(tmp, "%c", text[i]);
			strcat(fileName, tmp);
			continue;
		}
		if (isFileName == 1 && text[i] == '\n') {
			isFileName = 0;
			isWordCurent = 1;
			wordCurent = "";
			wordCurent = malloc(KSIZEWORD);
			continue;
		}
		if (isWordCurent == 1 && text[i] != ' ' && text[i] != '\n') {
			tmp = malloc(sizeof(char));
			sprintf(tmp, "%c", text[i]);
			strcat(wordCurent, tmp);
			continue;
		}
		if (isWordCurent == 1 && text[i] == ' ') {
			isWordCurent = 0;
			isNumberOccurenceCurent = 1;
			numberOccurenceCurent = "";
			numberOccurenceCurent = malloc(KSIZEWORD);
			continue;
		}
		if (isNumberOccurenceCurent == 1 && text[i] != '\n') {
			tmp = malloc(sizeof(char));
			sprintf(tmp, "%c", text[i]);
			strcat(numberOccurenceCurent, tmp);
			continue;
		}
		if (isNumberOccurenceCurent == 1 && text[i] == '\n') {
			sscanf(numberOccurenceCurent, "%d", &intNumberOccurenceCurent);
			add_value_MapOfMap(&map, wordCurent, fileName,
					intNumberOccurenceCurent);
			isWordCurent = 1;
			isNumberOccurenceCurent = 0;
			wordCurent = "";
			wordCurent = malloc(KSIZEWORD);
			continue;
		}
	}

	FILE* fileIndex = fopen(index_path, "w+");

	if (fileIndex != NULL) {
		while (map != NULL) {
			fputs(pop_value_MapOfMap(&map), fileIndex);
		}
	}
}

