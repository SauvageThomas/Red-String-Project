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

void init_MapOfMap(MapOfMap* map) {
	*map = NULL;
}

void free_MapOfMap(MapOfMap map) {
	while (map != NULL) {
		MapOfMap  old = map;
		map = (MapOfMap ) ((cellMapOfMap*) map)->next;
		free(old->key);
		free(old);
	}
	//free(map);
}

cellMapOfMap* find_value_MapOfMap(cellMapOfMap* cell, char* key) {
	if (cell == NULL)
		return NULL;
	if (strcmp(cell->key, key) == 0)
		return cell;
	return find_value_MapOfMap(cell->next, key);
}

void add_value_MapOfMap(MapOfMap* map, char* key, char* key_of_second_map,
		int nb_occurence) {
	cellMapOfMap* cellTmp = find_value_MapOfMap(*map, key);
	if (cellTmp == NULL) {
		MapOfMap map2 = malloc(sizeof(cellMapOfMap));

		init_hash_map(&((cellMapOfMap*) map2)->map);
		add_value_hash_map_with_value(&((cellMapOfMap*) map2)->map,
				key_of_second_map, nb_occurence);

		((cellMapOfMap*) map2)->key = key;
		((cellMapOfMap*) map2)->next = *map;
		*map = map2;
	} else {
		add_value_hash_map_with_value(&cellTmp->map, key_of_second_map,
				nb_occurence);
	}
}

void remove_cellMapOfMap(MapOfMap* map, char* key) {
	if ((*map)->key == key) {
		(*map) = (*map)->next;
	} else
		remove_cellMapOfMap(&(*map)->next, key);

}


int is_MapOfMap_empty(MapOfMap map){
	if(map==NULL)
		return 1;
	return 0;
}

HashMap* get_hashMap_with_key(MapOfMap map, char* key){

	while (map != NULL) {
		if (strcmp(map->key, key) == 0) {
			return &map->map;
		}
		map = map->next;
	}	
	assert(map==NULL);

}	


//return the first cell, it remove this cell of the map in the same time 
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

