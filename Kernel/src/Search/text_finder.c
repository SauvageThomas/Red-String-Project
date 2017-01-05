
#include "text_finder.h"
#include "../Tools/data_handler.h"

void find_text(DataFile df){
	printf("XML FILE\n");
	char* content = read_string_from_file(df);
	content = remove_xml(content); //TODO: remove "<...>", ".?!...", word < 3char
	content = remove_punctuation(content);
	content = remove_words(content);

	//TODO: compare with index and get the similar files
}

char * remove_xml(char* content){
	char* shortened = (char *) malloc(sizeof(char) * (int)strlen(content));
	char* new_content;
	int check = 1;
	for (size_t i = 0; i < strlen(content); i++) {
		char tmp = content[i];
		if (tmp == '<') {
			check = 0;
		} else if (check) {
			strncat(shortened, &tmp, 1);
		} else if (tmp == '>'){
			check = 1;
		}
	}
	newContent = (char *) malloc(sizeof(char) * (int)strlen(shortened));
	strcpy(newContent, shortened);
	free(shortened);
	return newContent;
}

char* remove_punctuation(char* content){
	char punctuation[6] = ",;.:!?";
	char* shortened = (char *) malloc(sizeof(char) * (int)strlen(content));
	char* newContent;
	int check;
	for (size_t i = 0; i < strlen(content); i++) {
		char tmp = content[i];
    check = 1;
		for (size_t j = 0; j < strlen(punctuation); j++) {
			if (tmp == punctuation[j]) check = 0;
		}
		if (check) {
			strncat(shortened, &tmp, 1);
		}
	}
	newContent = (char *) malloc(sizeof(char) * (int)strlen(shortened));
	strcpy(newContent, shortened);
	free(shortened);
	return newContent;
}

char* remove_words(char* content){

	return content;
}
