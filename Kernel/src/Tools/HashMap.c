#include "HashMap.h"
#include <malloc.h>



void init(HashMap* map){
	*map = NULL;
}

CellHashMap* findValue(CellHashMap* cell, char* key){

	if(cell == NULL)
		return NULL;
	if(cell->key == key)
		return cell;
	return findValue(cell->next, key);
}

void addValue(HashMap* map, char* key, int nbOccurence){
	CellHashMap* cellTmp = findValue(*map,key);
	if(cellTmp == NULL){
		HashMap map2 = (HashMap)malloc(sizeof(CellHashMap));
		((CellHashMap*)map2)->key = key;
		map2->nbOccurence = nbOccurence;
		((CellHashMap*)map2)->next = *map;
		*map = map2;
	}else{
		cellTmp->nbOccurence+=nbOccurence;
	}
}


void displayMap(HashMap map){
	if(map!=NULL){
		printf("key : %s    nbOccurence : %d\n", map->key, map->nbOccurence );
		displayMap((HashMap)((CellHashMap*)map)->next);
	}
}

