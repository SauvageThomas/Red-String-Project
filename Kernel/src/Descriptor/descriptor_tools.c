#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../Data/constant.h"

//Right now only work for image and text (not tested yet, waiting for descriptor_extractor)
int compare_descriptors(Descriptor desc1, Descriptor desc2) {
	CellHashMap* map1 = desc1.map;
	CellHashMap* map2 = desc2.map;

	int common = 0;
	while (map1 != NULL) {
		while (map2 != NULL) {
			if (!strcmp(map1->key, map2->key)) {
				common += 1;
			}
			map2 = map2->next;
		}
		map1 = map1->next;
	}
}
