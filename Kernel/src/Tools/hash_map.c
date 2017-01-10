#include "hash_map.h"
#include <malloc.h>



void init_hashmap(HashMap* map){
	*map = NULL;
}

CellHashMap* find_value(CellHashMap* cell, char* key){

	if(cell == NULL)
		return NULL;
	if(cell->key == key)
		return cell;
	return find_value(cell->next, key);
}

//if the map don't yet contain the "key", this "key" is add with 1 occurrence
//else the nombre od occurrence is incremented by one 
void add_value(HashMap* map, char* key){
	CellHashMap* cellTmp = find_value(*map,key);
	if(cellTmp == NULL){
		HashMap map2 = (HashMap)malloc(sizeof(CellHashMap));
		((CellHashMap*)map2)->key = key;
		map2->nbOccurence = 1;
		((CellHashMap*)map2)->next = *map;
		*map = map2;
	}else{
		cellTmp->nbOccurence += 1;
	}
}

//return the number of occurrence of the "key"
int find_nb_occurence(HashMap map,char* key){
	CellHashMap* cellTmp = find_value(map,key);
	if(cellTmp == NULL)
		return 0;
	return cellTmp->nbOccurence;
	
}

void remove_cell_hashmap(HashMap* map, char* key){
	if((*map)->key == key){
		(*map) = (*map)->next;
	}
	else
		remove_cell_hashmap(&(*map)->next, key);
	
}

//return the cell which contain most occurrence, this method remove this cell of the map in the same time 
CellHashMap pop(HashMap* map){
	CellHashMap* cellTmp = *map;
	CellHashMap result = **map;
	while(cellTmp!= NULL){
		if(cellTmp->nbOccurence > result.nbOccurence)
			result = *cellTmp;
		cellTmp = cellTmp->next;
	}
	if(*map!=NULL)
		remove_cell_hashmap(map,result.key);
	return result;
}

//Multiply the number of occurrences of the cell referenced by "key"
void multiplay_val_of_cell(HashMap* map, char* key, int multiplier){
	find_value(*map,key)->nbOccurence *= multiplier; 
}


//return a string wich describe the map
// ex : 
//		chien 3
//		chat 2
//		poisson 5

char* display_map(HashMap map){
	char* result ="";
	char nb_occurence[4];
	char* tmp;
	char* tmp2;
	size_t length;
	while(map!=NULL){
		sprintf(nb_occurence,"%d",map->nbOccurence);
		length = strlen(map->key) + strlen(nb_occurence) + 1; 
		tmp = malloc(length);
		strcpy(tmp,map->key);
		strcat(tmp, " "); 
		strcat(tmp, nb_occurence);
		strcat(tmp, "\n");  
		length = strlen(result) + strlen(tmp);
		tmp2 = malloc(length);
		strcpy(tmp2,result);
		strcat(tmp2,tmp);
		length = strlen(tmp2);
		result = malloc(length);
		strcpy( result, tmp2);
        map = (HashMap)((CellHashMap*)map)->next;
	}
	return result;
}


/*
int main(){
	HashMap map;
	init_hashmap(&map);
	add_value(&map,"chien");
	add_value(&map,"chat");
	add_value(&map,"chien");
	add_value(&map,"chat");
	add_value(&map,"chien");
	add_value(&map,"kebab");
	add_value(&map,"kebab");
	add_value(&map,"kebab");
	add_value(&map,"chat");
	add_value(&map,"chien");
	add_value(&map,"chien");
	//printf("Il y a %d chien(s)\n",find_nb_occurence(map, "chien"));
	//printf("Il y a %d chat(s)\n",find_nb_occurence(map, "chat"));
	//printf("Il y a %d pigeon(s)\n",find_nb_occurence(map, "pigeon"));
	//printf("%s",display_map(map));
	//printf("Element enlevé est : %s\n",pop(&map).key);
	multiplay_val_of_cell(&map,"chien",10);
	multiplay_val_of_cell(&map,"chat",2);
	printf("%s",display_map(map));
}*/
