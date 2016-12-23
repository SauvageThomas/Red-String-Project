/*
 * tools.h
 *
 *  Created on: 30 nov. 2016
 *      Author: THOMAS
 */

#ifndef TOOLS_DATA_HANDLER_H_
#define TOOLS_DATA_HANDLER_H_

int is_empty_file(char* path);
char *read_string_from_file(char *path);
void write_string_in_file(char *path, char *string);

#endif /* TOOLS_DATA_HANDLER_H_ */
