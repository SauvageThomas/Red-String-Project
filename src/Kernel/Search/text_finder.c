#include "text_finder.h"

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
	}
	working_content[cpt] = '\0';
	return working_content;
}

void remove_punctuation(char* content) {
	char punctuation[] = "\"/,;.:!?()\n";
	//char* working_content = malloc(sizeof(char) * (int) strlen(content));
	char* final_content;
	char tmp;
	for (size_t i = 0; i < strlen(content); i++) {
		tmp = content[i];
		if (tmp >= 65 && tmp <= 90)	//MAJ -> min
			content[i] += 32;
		else if (tmp == -55 || (tmp >= -24 && tmp <= -22))//è, é, ë, É -> e
			content[i] = 101;
		else if (tmp == -25)	//ç ->c
			content[i] = 99;
		else if (tmp == -18)	//î ->i
			content[i] = 105;
		else if (tmp == -12)	//ô ->o
			content[i] = 111;
		else if (tmp == -32 || tmp == -30)	//â, à ->a
			content[i] = 97;

		for (size_t j = 0; j < strlen(punctuation); j++) {
			if (tmp == punctuation[j]) {
				content[i] = ' ';
				break;
			}
		}
	}
}

char** remove_words(char* content, int *matrix_length) {
	// maximum length of a french word is 24 and a word may have at least 3 letters within

	char ** matrix_of_words = malloc(strlen(content) * sizeof(char*) * 2);
	if (matrix_of_words == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}
	for (int i = 0; i < strlen(content); i++)
		matrix_of_words[i] = malloc(KSIZEWORD * sizeof(char) * 2);

	size_t cpt = 0, cpt1 = 0, cpt2 = 0;
	char tmp = content[cpt];
	while (tmp != '\0') {
		if (tmp != ' ') {
			if (tmp == 39)	// remove the '
				cpt2 = 0;
			else {
				matrix_of_words[cpt1][cpt2] = tmp;
				cpt2++;
			}
		}
		else {
			if (cpt2 > 3){
				matrix_of_words[cpt1][cpt2] = '\0';
				cpt1++;
			}
			cpt2 = 0;
		}
		cpt++;
		tmp = content[cpt];
	}
	*matrix_length = cpt1;
	return matrix_of_words;
}
