#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "text_finder.h"

void find_text(DataFile df) {
	int matrix_length = 0;
	printf("XML FILE\n");
	/*
	 char* content = read_string_from_file(df);
	 content = remove_xml(content);
	 content = remove_punctuation(content);

	 char **matrix_of_words = remove_words(content, &matrix_length);
	 //printf("%s\n", content);
	 //for (int i=0; i<matrix_length; i++)   /* test loop*/
	//printf("%s\n", matrix_of_words[i]);
	//TODO: compare with index and get the similar files
}

char *remove_xml(char* content) {
	char* working_content = malloc(sizeof(char) * (int) strlen(content));
	if (working_content == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}
	char* final_content;
	int cpt = 0, check = 1;
	for (size_t i = 0; i < strlen(content); i++) {
		char tmp = content[i];

		if (tmp == '<') {
			check = 0;
		} else if (check) {
			working_content[cpt] = tmp;
			cpt++;
		} else if (tmp == '>') {
			check = 1;
		}
	}/*
	 final_content = malloc(sizeof(char) * cpt);
	 for (size_t i = 0; i < cpt; i++)
	 final_content[i] = working_content[i];

	 final_content[cpt] = '\0';
	 //free(working_content);
	 puts("end");*/
	working_content[cpt] = '\0';
	return working_content;
}

void remove_punctuation(char* content) {
	char punctuation[] = "/,;.:!?()\n";
	//char* working_content = malloc(sizeof(char) * (int) strlen(content));
	char* final_content;
	int check;
	char tmp;

	for (size_t i = 0; i < strlen(content); i++) {
		tmp = content[i];
		check = 1;

		for (size_t j = 0; j < strlen(punctuation); j++) {
			if (tmp == punctuation[j] || tmp == 34) {	// remove the "
			//working_content[i] = ' ';
			//tmp = ' ';
				content[i] = ' ';
				check = 0;
				break;
			}
		}
		//putchar(tmp);
		//working_content[i] = tmp;
		/*
		 if (check) {
		 strncat(working_content, &tmp, 1);
		 }*/
	}
	/*working_content[strlen(content)] = '\0';/*
	 final_content = malloc(sizeof(char) * (int) strlen(working_content));
	 strcpy(final_content, working_content);*/
	//free(working_content);
	//return content;
}

char** remove_words(char* content, int *matrix_length) {
	// maximum length of a french word is 24 and a word may have at least 3 letters within

	//printf("%s\n", content);

	char ** matrix_of_words = malloc(strlen(content) * sizeof(char*));
	if (matrix_of_words == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}
	for (int i = 0; i < strlen(content); i++)
		//matrix_of_words[i] = calloc(KSIZEWORD, sizeof(char));
		matrix_of_words[i] = malloc(KSIZEWORD * sizeof(char));

	size_t cpt = 0, cpt1 = 0, cpt2 = 0;
	char tmp = content[cpt];
	while (tmp != '\0') {
		//putchar(tmp);
		if (tmp != ' ') {
			if (tmp == 39)	// remove the '
				cpt2 = 0;
			else {
				if (tmp >= 65 && tmp <= 90)	//MAJ -> min
					tmp += 32;
				else if (tmp == -55 || (tmp >= -24 && tmp <= -22))//è, é, ë, É -> e
					tmp = 101;
				else if (tmp == -25)	//ç ->c
					tmp = 99;
				else if (tmp == -18)	//î ->i
					tmp = 105;
				else if (tmp == -12)	//ô ->o
					tmp = 111;
				else if (tmp == -32 || tmp == -30)	//â, à ->a
					tmp = 97;
				matrix_of_words[cpt1][cpt2] = tmp;
				cpt2++;
			}
		} else {
			if (cpt2 > 3)
				cpt1++;
			cpt2 = 0;
		}
		cpt++;
		tmp = content[cpt];
	}

	*matrix_length = cpt1;
	return matrix_of_words;
}

