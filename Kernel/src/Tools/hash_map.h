/*
 ============================================================================
 Name        : hash_map.c
 Author      : Pierre
 Version     :
 Description : the implementation of a specific HashMap
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

typedef struct cell{
	char* key;
	int nbOccurence;
	struct cell* next;
	
}CellHashMap;

typedef CellHashMap* HashMap; 

void init_hash_map(HashMap* map);
void add_value_hash_map(HashMap* map, char* key);
char* print_hash_map(HashMap map);
int find_nb_occurence(HashMap map,char* key);
char* pop_value_hash_map(HashMap* map);
void multiplay_val_of_cell(HashMap* map, char* key, int multiplier);