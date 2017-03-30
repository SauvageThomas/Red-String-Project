/*
 ============================================================================
 Name        : map_of_map.c
 Author      : Pierre
 Version     :
 Description : the implementation of a map whose values are maps
 ============================================================================
 */

#include <malloc.h>
#include <assert.h>
#include "map_of_map.h"

//intialize the mapOfMap
void init_MapOfMap(MapOfMap* map) {
	*map = NULL;
}

//free the memory taken by the map
void free_MapOfMap(MapOfMap map) {
	while (map != NULL) {
		MapOfMap  old = map;
		map = (MapOfMap ) ((cellMapOfMap*) map)->next;
		free(old->key);
		free(old);
	}
	//free(map);
}

//return the cell wich contain a map and the "key" which referenced this cell (tanks to the "key")
cellMapOfMap* find_value_MapOfMap(cellMapOfMap* cell, char* key) {
	if (cell == NULL)
		return NULL;
	if (strcmp(cell->key, key) == 0)
		return cell;
	return find_value_MapOfMap(cell->next, key);
}

//increment of one the value referenced by "key_of_second_map" of the map referenced by "key"
void add_value_MapOfMap(MapOfMap* map, char* key, char* key_of_second_map,
		int nb_occurence) {
	cellMapOfMap* cellTmp = find_value_MapOfMap(*map, key);
	if (cellTmp == NULL) {
		MapOfMap map2 = malloc(sizeof(cellMapOfMap));

		init_hash_map(&((cellMapOfMap*) map2)->map);
		add_nb_value_hash_map(&((cellMapOfMap*) map2)->map,
				key_of_second_map, nb_occurence);

		((cellMapOfMap*) map2)->key = key;
		((cellMapOfMap*) map2)->next = *map;
		*map = map2;
	} else {
		add_nb_value_hash_map(&cellTmp->map, key_of_second_map,
				nb_occurence);
	}
}

//remove the cell referenced by "key"
void remove_cellMapOfMap(MapOfMap* map, char* key) {
	if ((*map)->key == key) {
		(*map) = (*map)->next;
	} else
		remove_cellMapOfMap(&(*map)->next, key);

}

//return 1 if map is empty, 0 else
int is_MapOfMap_empty(MapOfMap map){
	if(map==NULL)
		return 1;
	return 0;
}

//return the hashMap in the cell referenced by "key"
HashMap* get_hashMap_with_key(MapOfMap map, char* key){
	while (map != NULL) {
		if (strcmp(map->key, key) == 0) {
			return &map->map;
		}
		map = map->next;
	}	
	assert(map==NULL);

}	


//return a description of the first cell(in alphabetical_order), it removes this cell of the map in the same time 
char* pop_value_MapOfMap(MapOfMap* map) {
	cellMapOfMap* cellTmp = *map;
	cellMapOfMap* first_cell_alphabetical_order = *map;
	char* first_key_alphabetical_order = cellTmp->key;
	while (cellTmp != NULL) {
		if (strcmp(cellTmp->key, first_key_alphabetical_order) < 0) {
			first_cell_alphabetical_order = cellTmp;
			first_key_alphabetical_order = cellTmp->key;
		}
		cellTmp = cellTmp->next;
	}

	char* result = malloc(
			strlen(first_cell_alphabetical_order->key) + sizeof(int)
					+ size_of_map(first_cell_alphabetical_order->map) + 5);
	char* pattern = "%c%s \n";
	sprintf(result,pattern,'>',first_cell_alphabetical_order->key);
	while(size_of_map(first_cell_alphabetical_order->map)>0) {
		strcat(result, pop_value_hash_map(&first_cell_alphabetical_order->map));
	}

	if (*map != NULL)
		remove_cellMapOfMap(map, first_cell_alphabetical_order->key);
	return result;
}

