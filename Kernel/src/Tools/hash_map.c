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

CellHashMap* find_value(CellHashMap* cell, char* key) {
	if (cell == NULL)
		return NULL;
	if (strcmp(cell->key, key) == 0)
		return cell;
	return find_value(cell->next, key);
}

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
//else the nombre od occurrence is incremented by one 
void add_value_hash_map(HashMap* map, char* key) {
	CellHashMap* cellTmp = find_value(*map, key);
	if (cellTmp == NULL) {
		HashMap map2 = malloc(sizeof(CellHashMap));

		printf("New key : %s\n", key);
		((CellHashMap*) map2)->key = malloc(strlen(key) + 1);
		strcpy(((CellHashMap*) map2)->key, key);

		//((CellHashMap*) map2)->key = key;
		map2->nbOccurence = 1;
		((CellHashMap*) map2)->next = *map;
		*map = map2;
	} else {

		cellTmp->nbOccurence += 1;
		printf("Alredy got : %s => %d\n", key, cellTmp->nbOccurence);
	}
}

//return the number of occurrence of the "key"
int find_nb_occurence(HashMap map, char* key) {
	CellHashMap* cellTmp = find_value(map, key);
	if (cellTmp == NULL)
		return 0;
	return cellTmp->nbOccurence;

}

void remove_cell_hashmap(HashMap* map, char* key) {
	if ((*map)->key == key) {
		(*map) = (*map)->next;
	} else
		remove_cell_hashmap(&(*map)->next, key);

}

//return the cell which contain most occurrence, this method remove this cell of the map in the same time 
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

//return a string wich describe the map
// ex : 
//		chien 3
//		chat 2
//		poisson 5

char* print_hash_map(HashMap map) {
	puts("heeeeeeeeeey");
	char* result = "";
	char nb_occurence[4];
	char* tmp;
	char* tmp2;
	size_t length;
	while (map != NULL) {
		sprintf(nb_occurence, "%d", map->nbOccurence);
		length = strlen(map->key) + strlen(nb_occurence) + 1;
		tmp = malloc(length);
		strcpy(tmp, map->key);
		strcat(tmp, " ");
		strcat(tmp, nb_occurence);
		strcat(tmp, "\n");
		length = strlen(result) + strlen(tmp);
		tmp2 = malloc(length);
		strcpy(tmp2, result);
		strcat(tmp2, tmp);
		length = strlen(tmp2);
		result = malloc(length);
		strcpy(result, tmp2);
		map = (HashMap) ((CellHashMap*) map)->next;
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
