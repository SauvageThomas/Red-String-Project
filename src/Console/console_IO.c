
#include "console_IO.h"

void input_error(char *input) {
	/*
	Display an error message
	*/
	printf("command not found : %s ! Please, try again.\n", input);
}

void get_input(char* buffer) {
	/*
	Get the input for the menu, only 1 digit
	*/
	while (get_secure_input(buffer, 2) != 1) {
		puts("1 digit was expected, please try again !");
	}
}

void clear_console() {
	/*
	Clear the console
	*/
	printf("\033[H\033[J\n");
}