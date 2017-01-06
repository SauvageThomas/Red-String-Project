#include <string.h>
#include "text_finder.h"
#include "../Tools/data_handler.h"

void find_text(DataFile df){
	printf("XML FILE\n");
	char* content = read_string_from_file(df);
	content = remove_xml(content); //TODO: remove "<...>", ".?!...", word < 3char
	content = remove_punctuation(content);
	content = remove_words(content);
	printf("%s", content);

	//TODO: compare with index and get the similar files
}

char * remove_xml(char* content){
	char* working_content = (char *) malloc(sizeof(char) * (int)strlen(content));
	printf("\n%d content\n", strlen(content));
	char* final_content;
	int cpt=0, check = 1;
	for (size_t i = 0; i < strlen(content); i++) {
		 char tmp = content[i];
		if (tmp == '<') {
			check = 0;
		} else if (check) {

			working_content[cpt]=tmp;
			cpt++;
		} else if (tmp == '>'){
			check = 1;
		}
	}
	final_content = (char *) malloc(sizeof(char) * cpt);
	for (size_t i= 0; i<cpt; i++)
		final_content[i]=working_content[i];
	//free(working_content);
	return final_content;
}

char* remove_punctuation(char* content){
	char punctuation[8] = ",;.:!?()";
	char* working_content = (char *) malloc(sizeof(char) * (int)strlen(content));
	char* final_content;
	int check;
	char tmp;
	for (size_t i = 0; i < strlen(content); i++) {
		tmp = content[i];
    	check = 1;
		for (size_t j = 0; j < strlen(punctuation); j++) {
			if (tmp == punctuation[j]) check = 0;
		}
		if (check) {
			strncat(working_content, &tmp, 1);
		}
	}
	final_content = (char *) malloc(sizeof(char) * (int)strlen(working_content));
	strcpy(final_content, working_content);
	//printf("%s", final_content);
	//free(working_content);
	return final_content;
}

char* remove_words(char* content){
	//char **
	return content;
}

