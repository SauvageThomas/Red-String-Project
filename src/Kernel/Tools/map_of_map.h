/*
 ============================================================================
 Name        : map_of_map.h
 Author      : Pierre
 Version     :
 Description : the implementation of a map whose values are maps
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "hash_map.h"


typedef struct cell_map_of_map{
	char* key;
	HashMap map;
	struct cell_map_of_map* next;

}CellMapOfMap;

typedef CellMapOfMap* MapOfMap;

void init_map_of_map(MapOfMap* map);
void add_value_map_of_map(MapOfMap* map, char* key, char* key_of_second_map, int nb_occurence);
char* pop_value_map_of_map(MapOfMap* map);
int is_map_of_map_empty(MapOfMap map);

