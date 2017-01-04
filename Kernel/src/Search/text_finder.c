
#include "text_finder.h"
#include "../Tools/data_handler.h"

void find_text(DataFile df){
	printf("XML FILE\n");
	char* content = read_string_from_file(df);
	content = remove_xml(content); //TODO: remove "<...>", ".?!...", word < 3char
	content = remove_punctuation(content);
	content = remove_words(content);

	//TODO: compare with index and get the similar files 
}

char * remove_xml(char* content){
	return content;
}
	
char* remove_punctuation(char* content){
	return content;
}

char* remove_words(char* content){
	return content;
}