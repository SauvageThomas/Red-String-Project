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

Descriptor *extract_all_descriptor(char *content, int *size_desc) {
	int size = 150;
	Descriptor *descriptors = malloc(sizeof(Descriptor) * size);

	int i;
	int cpt = 0;
	size_t max = strlen(content);
	for (i = 0; cpt < max; i += 1) {
		//printf("%d\n", i);


		//Remove the '>'
		cpt +=1;
		if (i >= size - 1) {
			puts("realloc");
			size *= 2;

			descriptors = realloc(descriptors, sizeof(descriptors) * size);
		}
		//printf("max %d\n", max);
		//printf("all %u 1 %u / %u\n", sizeof(descriptors), sizeof(descriptors[i]),  sizeof(Descriptor));

		descriptors[i].map = NULL;
		descriptors[i].size = max;


		//Read header
		int tmp = 0;
		while (content[cpt] != '\n') {
			//putchar(content[cpt]);
			descriptors[i].file_name[tmp] = content[cpt];
			tmp += 1;
			cpt += 1;
		}
		descriptors[i].file_name[tmp] = '\0';
		//printf("file_name %s\n", descriptors[i].file_name);

		//Remove the newline
		cpt += 1;

		//Add data to the map
		char *key = malloc(KSIZEWORD);
		while (content[cpt] != '>' && cpt <= max) {

			int n;
			//printf("line %s\n", line);
			sscanf(&content[cpt], "%s %d", key, &n);

			while (content[cpt] != '\n') {
				//putchar(content[cpt]);
				cpt += 1;
			}
			//Remove the newline
			cpt += 1;

			//puts("before");
			add_nb_value_hash_map(&(descriptors[i].map), key, n);

			//printf("cont %d\n", strlen(content));
			//printf("[%d/%d]%s => %d\n", cpt, max, key, n);
		}
		size += 1;
	}

	*size_desc = i;
	return descriptors;
}
