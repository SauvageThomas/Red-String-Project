/*
 ============================================================================
 Name        : map_of_map.c
 Author      : Pierre
 Version     :
 Description : the implementation of a map whose values are maps
 ============================================================================
 */


#include <malloc.h>
#include "map_of_map.h"


void init_map_of_map(map_of_map* map) {
	*map = NULL;
}


cell_map_of_map* find_value_map_of_map(cell_map_of_map* cell, char* key) {
	if (cell == NULL)
		return NULL;
	if (strcmp(cell->key, key) == 0)
		return cell;
	return find_value_map_of_map(cell->next, key);
}



void add_value_map_of_map(map_of_map* map, char* key, char* key_of_second_map, int nb_occurence) {
	cell_map_of_map* cellTmp = find_value_map_of_map(*map, key);
	if (cellTmp == NULL) {
		map_of_map map2 = malloc(sizeof(cell_map_of_map));

		init_hash_map(&((cell_map_of_map*) map2)->map);
		add_value_hash_map_with_value(&((cell_map_of_map*) map2)->map, key_of_second_map, nb_occurence);
		
		((cell_map_of_map*) map2)->key =  key;
		((cell_map_of_map*) map2)->next = *map;
		*map = map2;
	} else {
		add_value_hash_map_with_value(&cellTmp->map, key_of_second_map, nb_occurence);
	}
}


void remove_cell_map_of_map(map_of_map* map, char* key) {
	if ((*map)->key == key) {
		(*map) = (*map)->next;
	} else
		remove_cell_map_of_map(&(*map)->next, key);

}

int is_map_of_map_empty(map_of_map map){
	if(map==NULL)
		return 1;
	return 0;
}

//return the first cell, it remove this cell of the map in the same time 
char* pop_value_map_of_map(map_of_map* map) {
	cell_map_of_map* cellTmp = *map;
	cell_map_of_map* first_cell_alphabetical_order = *map;
	char* first_key_alphabetical_order = cellTmp->key;
	while (cellTmp != NULL) {
		if (strcmp(cellTmp->key, first_key_alphabetical_order) < 0) {
			first_cell_alphabetical_order = cellTmp;
			first_key_alphabetical_order = cellTmp->key;
		}
		cellTmp = cellTmp->next;
	}
	
	char* result = malloc(strlen(first_cell_alphabetical_order->key) + sizeof(int) + size_of_map(first_cell_alphabetical_order->map)+ 5);
	char* pattern = ">%s \n";
	sprintf(result, pattern,first_cell_alphabetical_order->key);

	while(size_of_map(first_cell_alphabetical_order->map)>0){
		strcat(result, pop_value_hash_map(&first_cell_alphabetical_order->map));
	}

	if (*map != NULL)
		remove_cell_map_of_map(map, first_cell_alphabetical_order->key);
	return result;
}


