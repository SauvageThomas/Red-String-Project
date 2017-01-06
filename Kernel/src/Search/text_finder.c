#include <string.h>
#include <malloc.h>
#include "text_finder.h"
#include "../Tools/data_handler.h"

void find_text(DataFile df){
	int matrix_length=0;
	printf("XML FILE\n");
	char* content = read_string_from_file(df);
	content = remove_xml(content); //TODO: remove "<...>", ".?!...", word < 3char
	content = remove_punctuation(content);
	printf("\n%d content\n", strlen(content));
	char **matrix_of_words = (char**)malloc((int)strlen(content) * sizeof(char*));
	matrix_of_words = remove_words(content, &matrix_length);
	printf("\n%d matrix_length\n", matrix_length);
	printf("%s", content);
	//for (int i=0; i<matrix_length; i++)
	//		printf("%s\n", matrix_of_words[i]);
	//TODO: compare with index and get the similar files
}

char * remove_xml(char* content){
	char* working_content = (char *) malloc(sizeof(char) * (int)strlen(content));
	///printf("\n%d content\n", strlen(content));
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
	char punctuation[9] = ",;.:!?()\n";
	char* working_content = (char *) malloc(sizeof(char) * (int)strlen(content));
	char* final_content;
	int check;
	char tmp;
	for (size_t i = 0; i < strlen(content); i++) {
		tmp = content[i];
    	check = 1;
		for (size_t j = 0; j < strlen(punctuation); j++) {
			if (tmp == punctuation[j]){
			working_content[i]=' ';
			check = 0;}
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

char** remove_words(char* content, int *matrix_length){
	// maximum length of a french word is 24 and a word may have at least 3 letters within
	char ** matrix_of_words=(char**) malloc ( strlen(content)*sizeof(char*));
	for (int i=0; i<strlen(content); i++)
		matrix_of_words[i]=(char*)malloc (24*sizeof(char));
	size_t cpt=0, cpt1=0, cpt2=0;
	char tmp=content[cpt];
	while (tmp !='\0'){
		if (tmp!=' '){
			if (tmp=''' || tmp
			matrix_of_words[cpt1][cpt2]=tmp;
			cpt2++;
		}
		else {
			if (cpt2>3){
				matrix_of_words[cpt1] = realloc(matrix_of_words[cpt1], cpt2);
				cpt1++;}
			cpt2=0;}		
		cpt++;
		tmp=content[cpt];
	}
	printf("\n%d cpt \n",cpt);
	*matrix_length=cpt1;
	return matrix_of_words;
}














