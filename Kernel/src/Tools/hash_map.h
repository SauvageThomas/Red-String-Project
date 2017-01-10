#include <stdio.h>
#include <string.h>

typedef struct cell{
	char* key;
	int nbOccurence;
	struct cell* next;
	
}CellHashMap;

typedef CellHashMap* HashMap; 

void init_hashmap(HashMap* map);
void add_value(HashMap* map, char* key);
char* display_map(HashMap map);
int find_nb_occurence(HashMap map,char* key);
CellHashMap pop(HashMap* map);
void multiplay_val_of_cell(HashMap* map, char* key, int multiplier);


