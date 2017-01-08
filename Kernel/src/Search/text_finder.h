
#ifndef SEARCH_TEXT_FINDER_H_
#define SEARCH_TEXT_FINDER_H_

#include "../Tools/data_handler.h"

void find_text(DataFile df);
char * remove_xml(char* content);
char* remove_punctuation(char* content);
char** remove_words(char* content, int* matrix_length);

#endif
