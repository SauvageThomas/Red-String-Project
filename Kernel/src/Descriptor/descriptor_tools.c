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

Descriptor *extract_first_descriptor(char *content, int *size_desc) {
	int size = 150;
	Descriptor *descriptors = malloc(sizeof(descriptors) * size);

	int i;
	for (i = 0; strlen(content) > 2; i += 1) {
		printf("%d\n", i);

		if (i >= size - 1) {
			//puts("realloc");
			size *= 2;

			descriptors = realloc(descriptors, sizeof(descriptors) * size);
		}

		descriptors[i].map = NULL;
		descriptors[i].size = strlen(content);

		//Remove the first char '<'
		content += 1;

		//Read header
		//char *tmp = malloc(strlen(content) + 1);
		//strcpy(tmp, content);

		char *token = "\n";
		char *name = strtok(content, token);
		strcpy(descriptors[i].file_name, name);

		printf("file_name %s\n", descriptors[i].file_name);

		while (*content != '\n') {
			content += 1;
		}

		//Remove the '\n'
		//content += 1;

		//Add data to the map
		char *token2 = "\n";
		char *key = malloc(KSIZEWORD);

		while (*content != '>' && strlen(content) > 2) {

			int n;
			char *line = strtok(content, token2);

			//printf("line %s\n", line);
			sscanf(line, "%s %d", key, &n);
			/*
			 key = strtok(content, token2);
			 value = strtok(NULL, token2);*/

			while (*content != '\n') {
				content += 1;
			}
			//Remove the newline
			content += 1;

			//int n = (int) strtol(value, (char **) NULL, 10);

			add_nb_value_hash_map(&descriptors[i].map, key, n);

			//printf("cont %d\n", strlen(content));
			//printf("[%c]%s => %d\n", *content, key, n);

		}

		//size += 1;
		//printf("%s\n", content);
		descriptors[i].size -= strlen(content) + 10;
	}
	//printf("%d\n", i);
	*size_desc = i;
	return descriptors;
}
