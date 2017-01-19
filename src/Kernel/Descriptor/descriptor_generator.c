/*
 * descriptor_generator.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */

#include "descriptor_generator.h"

int check_descriptor(DataFile df, DataFile *data_files, size_t size) {
	if (df.length == 0) {
		puts("no descriptor found !");
		return 1;
	}

	puts("Have to check every file...");

	char *content = read_string_from_file(df);

	int size_desc;

	Descriptor *desc = extract_all_descriptor(content, &size_desc);
	//printf("size desc : %d and nb files %u\n", size_desc, size);
	if (size != size_desc) {
		puts("size !=");
		return 1;
	}
	//For each file
	for (int i = 0; i < size; i += 1) {
		//If it's not a different file
		if (strlen(desc[i].file_name) == strlen(data_files[i].path)) {
			for (int j = 0; j < strlen(desc[i].file_name); j += 1) {

				if (desc[i].file_name[j] != data_files[i].path[j]) {
					puts("wrong");
					free(desc);
					free(content);
					return 1;
				}
			}
		}

		DataFile ressource = init_data_file(desc[i].file_name);
		if (ressource.date > df.date) {
			printf("File not up-to-date in descriptor : %s !\n", ressource.path);
			free(desc);
			free(content);
			return 1;
		}
		//free_map_of_map(desc[i].map);
	}

	puts("All the files are up-to-date in descriptor !");
	free(desc);
	free(content);
	return 0;
}

Descriptor init_descriptor(char* path) {
	time_t rawtime = time(NULL);
	Descriptor descriptor = { .map = NULL, .date = rawtime };
	strcpy(descriptor.file_name, path);
	return descriptor;
}

//Appends the descriptor at the end of the file
void descriptor_to_file(Descriptor descriptor, DataFile df) {
	if (descriptor.map == NULL) {
		puts("None");
		return;
	}

	char *result = malloc(descriptor.size);
	if (result == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}

	char date[50];
	sprintf(date, "%u\n", descriptor.date);

	strcpy(result, ">");
	strcat(result, descriptor.file_name);
	strcat(result, "\n");
	strcat(result, "\n");

	for (size_t i = 0; i < descriptor.nb_maps; i++) {
	char currentKey[5];
	sprintf(currentKey, "%zu", i);
	printf("%s\n", currentKey);
		while (*get_hashMap_with_key(descriptor.map, currentKey) != NULL) {
			char *tmp = pop_value_hash_map((get_hashMap_with_key(descriptor.map, currentKey)));
			strcat(result, tmp);
		}
		append_string_in_file(df, result);
	}

	//free_map_of_map(descriptor.map);
	free(result);
	result = NULL;
}

//Right now only work for image and text (not tested yet, waiting for descriptor_extractor)
int compare_descriptors(Descriptor desc1, Descriptor desc2) {
	CellHashMap* map1 = desc1.map;
	CellHashMap* map2 = desc2.map;

	int common = 0;
	while (map1 != NULL) {
		while (map2 != NULL) {

			if (!strcmp(map1->key, map2->key)) {
				//printf("%s vs %s\n", map1->key, map2->key);
				//puts("+1 !");
				common += (map1->nbOccurence * 10 + map2->nbOccurence);
				//common += 1 + map1->nbOccurence;
			}
			map2 = map2->next;
		}
		map2 = desc2.map;
		map1 = map1->next;
	}
	return common;
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
		cpt += 1;
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
