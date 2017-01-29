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

	size_t len = strlen(descriptor.file_name);

	char date[50];
	sprintf(date, "%u\n", descriptor.date);

	strcpy(result, ">");
	strcat(result, descriptor.file_name);
	strcat(result, "\n");
	strcat(result, "\n");

	for (size_t i = 0; i < descriptor.nb_maps; i++) {
	char currentKey[5];
	sprintf(currentKey, "%zu", i);

	char** tableau = malloc(sizeof(char*) * descriptor.nb_intervalles);
	for (size_t i = 0; i < (descriptor.nb_intervalles); i++) {
		tableau[i] = NULL;
	}

		while (*get_hashMap_with_key(descriptor.map, currentKey) != NULL) {
			char *tmp = pop_value_hash_map((get_hashMap_with_key(descriptor.map, currentKey)));

			if (descriptor.file_name[len-1] == 'v') {
				char *p;
	    	p = strtok(tmp, " ");
				int a = atoi(p);
				tableau[a] = strtok(strtok(NULL, " "), "\n");
			} else {
				strcat(result, tmp);
			}
		}

		if (descriptor.file_name[len-1] == 'v') {
			char* ligne = malloc(3 * descriptor.nb_intervalles);
			memset(&ligne[0], 0, sizeof(ligne));
			for (size_t i = 0; i < descriptor.nb_intervalles; i++) {
				if (tableau[i] == NULL) {
					strcat(ligne, "0 ");
				} else {
					strcat(ligne, strcat(tableau[i], " "));
				}
			}
			strcat(result, ligne);
		}

		strcat(result, "\n");
		append_string_in_file(df, result);
		result = malloc(descriptor.size);
	}

	//free_map_of_map(descriptor.map);
	free(result);
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
				int min = map1->nbOccurence;
				if (min > map2->nbOccurence) {
					min = map2->nbOccurence;
				}
				common += min;
				//common += 1 + map1->nbOccurence;
			}
			map2 = map2->next;
		}
		map2 = desc2.map;
		map1 = map1->next;
	}
	return common;
}

int compare_sound_descriptors( Descriptor desc1, Descriptor desc2){// (not tested yet, waiting for descriptor_extractor)
	if (strcmp(desc1.file_name, desc2.file_name)){
		printf("both files are the same !\n");
		return 100;
	}
	else {
		double tmp, tmp2, moy=0.0;
		CellHashMap* map1 = desc1.map;
		CellHashMap* map2 = desc2.map;
		while (map1 != NULL && map2!=NULL) {
			if (!strcmp(map1->key, map2->key)) {
				moy+=1.0;
			}
			else{
				tmp= (double)strtol(map1->key, NULL, 10);
				tmp2= (double)strtol(map2->key, NULL, 10);
				if (tmp!=0&&tmp2!=0){
					if (tmp<tmp2)
						moy+= tmp/tmp2;
					if (tmp>tmp2)
						moy+= tmp2/tmp;
				}
			}
			map2 = map2->next;
			map1 = map1->next;
		}
		return moy/=desc1.size;
	}
	return 0;
}
Descriptor *extract_all_descriptor(char *content, int *size_desc) {
	int size = 350;
	Descriptor *descriptors = malloc(sizeof(Descriptor) * size);

	int i;
	int cpt = 0;
	size_t max = strlen(content);
	for (i = 0; cpt < max; i += 1) {
		//Remove the '>'
		cpt += 1;
		if (i >= size - 1) {
			size *= 2;

			descriptors = realloc(descriptors, sizeof(descriptors) * size);
		}
		descriptors[i].map = NULL;
		descriptors[i].size = max;

		//Read header
		int tmp = 0;
		while (content[cpt] != '\n') {
			descriptors[i].file_name[tmp] = content[cpt];
			tmp += 1;
			cpt += 1;
		}
		descriptors[i].file_name[tmp] = '\0';

		//Remove the newline
		cpt += 1;

		//Add data to the map
		char *key = malloc(KSIZE);
		while (content[cpt] != '>' && cpt < max) {
			int n;
			sscanf(&content[cpt], "%s %d", key, &n);

			while (content[cpt] != '\n') {
				//putchar(content[cpt]);
				cpt += 1;
			}
			//Remove the newline
			cpt += 1;
			add_nb_value_hash_map(&(descriptors[i].map), key, n);
		}
		free(key);
		size += 1;
	}
	*size_desc = i;
	return descriptors;
}

