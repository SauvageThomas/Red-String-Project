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

#ifndef TOOLS_MAP_OF_MAP_H_
#define TOOLS_MAP_OF_MAP_H_

typedef struct cellMapOfMapEt{
	char* key;
	HashMap map;
	struct cellMapOfMapEt* next;

}cellMapOfMap;

typedef cellMapOfMap* MapOfMap;

void init_MapOfMap(MapOfMap* map);
void add_value_MapOfMap(MapOfMap* map, char* key, char* key_of_second_map, int nb_occurence);
char* pop_value_MapOfMap(MapOfMap* map);
int is_MapOfMap_empty(MapOfMap map);
HashMap* get_hashMap_with_key(MapOfMap map, char* key);
void free_MapOfMap(MapOfMap map);

#endif /* TOOLS_MAP_OF_MAP_H_ */
