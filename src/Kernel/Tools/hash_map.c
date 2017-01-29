/*
 ============================================================================
 Name        : hash_map.c
 Author      : Pierre
 Version     :
 Description : the implementation of a specific HashMap
 ============================================================================
 */
#include "hash_map.h"
#include <malloc.h>

void init_hash_map(HashMap* map) {
	*map = NULL;
}

//find the value referenced by "key"
CellHashMap* find_value(CellHashMap* cell, char* key) {
	if (cell == NULL)
		return NULL;
	if (strcmp(cell->key, key) == 0)
		return cell;
	return find_value(cell->next, key);
}

//free the memory of the map
void free_map(HashMap map) {
	while (map != NULL) {
		HashMap old = map;
		map = (HashMap) ((CellHashMap*) map)->next;
		free(old->key);
		free(old);
	}
	//free(map);
}

//if the map don't yet contain the "key", this "key" is add with 1 occurrence
//else the nombre of occurrence is incremented by one 
void add_value_hash_map(HashMap* map, char* key) {
	CellHashMap* cellTmp = find_value(*map, key);
	if (cellTmp == NULL) {
		HashMap map2 = malloc(sizeof(CellHashMap));

		//printf("New key : %s\n", key);
		((CellHashMap*) map2)->key = malloc(strlen(key) + 1);
		strcpy(((CellHashMap*) map2)->key, key);

		//((CellHashMap*) map2)->key = key;
		map2->nbOccurence = 1;
		((CellHashMap*) map2)->next = *map;
		*map = map2;
	} else {
		cellTmp->nbOccurence += 1;
		//printf("Alredy got : %s => %d\n", key, cellTmp->nbOccurence);
	}
}

//if the map don't yet contain the "key", this "key" is add with nb_occurence occurrence
//else the nombre of occurrence is incremented by nb_occurence
void add_nb_value_hash_map(HashMap* map, char* key, int n) {
	CellHashMap* cellTmp = find_value(*map, key);
	if (cellTmp == NULL) {
		HashMap map2 = malloc(sizeof(CellHashMap));
		if(map2==NULL){
			perror("malloc");
		}
		((CellHashMap*) map2)->key = malloc(strlen(key) + 1);
		strcpy(((CellHashMap*) map2)->key, key);

		//((CellHashMap*) map2)->key = key;
		map2->nbOccurence = n;
		((CellHashMap*) map2)->next = *map;
		*map = map2;
	} else {
		cellTmp->nbOccurence += n;
		//printf("Alredy got : %s => %d\n", key, cellTmp->nbOccurence);
	}
}

//return the number of occurrence of the "key"
int find_nb_occurence(HashMap map, char* key) {
	CellHashMap* cellTmp = find_value(map, key);
	if (cellTmp == NULL)
		return 0;
	return cellTmp->nbOccurence;

}

//remove the cell identified by "key"
void remove_cell_hashmap(HashMap* map, char* key) {
	if ((*map)->key == key) {
		(*map) = (*map)->next;
	} else
		remove_cell_hashmap(&(*map)->next, key);

}

//return the cell which contain most occurrences, this method remove this cell of the map in the same time 
char* pop_value_hash_map(HashMap* map) {
	CellHashMap* cellTmp = *map;
	CellHashMap* max_occurences = *map;
	int max = cellTmp->nbOccurence;
	while (cellTmp != NULL) {
		if (cellTmp->nbOccurence > max) {
			max_occurences = cellTmp;
			max = max_occurences->nbOccurence;
		}
		cellTmp = cellTmp->next;
	}
	char* result = malloc(strlen(max_occurences->key) + sizeof(int) + 5);
	char* pattern = "%s %d\n";
	sprintf(result, pattern, max_occurences->key, max_occurences->nbOccurence);
	if (*map != NULL)
		remove_cell_hashmap(map, max_occurences->key);
	return result;
}

//Multiply the number of occurrences of the cell referenced by "key"
void multiplay_val_of_cell(HashMap* map, char* key, int multiplier) {
	find_value(*map, key)->nbOccurence *= multiplier;
}

//return the number of element of the map
int size_of_map(HashMap map){
	if(map==NULL)
		return 0;
	int result=0;
	while(map!=NULL){
		result++;
		map = map->next;
	}	
	return result;
}


/*
 int main(){
 HashMap map;
 init_hash_map(&map);
 add_value_hash_map(&map,"chien");
 add_value_hash_map(&map,"chat");
 add_value_hash_map(&map,"chien");
 add_value_hash_map(&map,"chat");
 add_value_hash_map(&map,"chien");
 add_value_hash_map(&map,"kebab");
 add_value_hash_map(&map,"kebab");
 add_value_hash_map(&map,"kebab");
 add_value_hash_map(&map,"chat");
 add_value_hash_map(&map,"chien");
 add_value_hash_map(&map,"chien");
 //printf("Il y a %d chien(s)\n",find_nb_occurence(map, "chien"));
 //printf("Il y a %d chat(s)\n",find_nb_occurence(map, "chat"));
 //printf("Il y a %d pigeon(s)\n",find_nb_occurence(map, "pigeon"));
 //printf("%s",display_map(map));
 //printf("Element enlevé est : %s\n",pop(&map).key);
 multiplay_val_of_cell(&map,"chien",10);
 multiplay_val_of_cell(&map,"chat",2);
 printf("%s",print_hash_map(map));
 return 0;
 }*/
