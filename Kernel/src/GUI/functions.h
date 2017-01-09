/*
 * functions.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#ifndef GUI_FUNCTIONS_H_
#define GUI_FUNCTIONS_H_

typedef struct {
	char** config;
	size_t size;
	size_t size_word;
} Config;

void xor_crypt(char *password);
char* get_value_of(Config config, const char* value);
Config load_config();
void wip();
void input_error(char *input);
int login();
void get_input(char* buffer, int* action);
void search_by_keyword();
void search_by_file();
void modif_config();

#endif /* GUI_FUNCTIONS_H_ */
