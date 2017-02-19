/*
 * data_manager.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */

#include "data_manager.h"


char* pretty_print_string(char *in) {
	/*
	Return a prettier char
	*/
	char *out = malloc(KSIZE + 15);
	out[0] = '\0';

	char c = in[0];
	int j = 0;
	while (c != '\0') {
		c = in[j];
		strncat(out, &c, 1);
		if (c == '/') {
			out[0] = '\0';
		} else if (c == ' ') {
			strcat(out, " -> ");
		}
		j += 1;
	}
	return out;
}

char *pretty_print_image(char *in) {
	/*
	Return a prettier string
	*/
	char *out = malloc(KSIZE + 15);
	out[0] = '\0';

	char c = in[0];
	int j = 0;
	while (c != '\0') {
		c = in[j];
		strncat(out, &c, 1);
		if (c == '/') {
			out[0] = '\0';
		} else if (c == ' ') {
			return out;
		}
		j += 1;
	}
	return NULL;
}

char *pretty_print_sound(char *in) {
	/*
	Return a prettier string
	*/
	return in;
}