#include <stdio.h>
#include <string.h>

typedef struct cell{
	char* key;
	int nbOccurence;
	struct cell* next;
	
}CellHashMap;

typedef CellHashMap* HashMap; 

void init(HashMap* map);
void addValue(HashMap* map, char* key, int nbOccurence);
void displayMap(HashMap map);


