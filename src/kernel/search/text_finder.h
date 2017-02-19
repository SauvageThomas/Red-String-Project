
#ifndef SEARCH_TEXT_FINDER_H_
#define SEARCH_TEXT_FINDER_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../Tools/data_handler.h"

char *remove_xml(char* content);
void remove_punctuation(char* content);
char** remove_words(char* content, int* matrix_length);

#endif
