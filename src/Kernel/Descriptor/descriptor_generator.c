/*
 * descriptor_generator.c
 *
 *  Created on: 5 déc. 2016
 *      Author: THOMAS
 */

#include "descriptor_generator.h"


Descriptor *extract_all_descriptor(char *content, int *size_desc) {
	/*
	Return every descriptors in the string content and its size size_desc
	*/
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


Descriptor *extract_all_descriptors(char *content, int *size_desc, enum FileType file_type) {
    int size = 350;
    int size2= size;
    Descriptor *descriptors = malloc(sizeof(Descriptor) * size);

    int i;
    int cpt = 0;
    size_t max = strlen(content);
    for (i = 0; cpt < max; i += 1) {
        //Remove the '>'
        cpt += 1;
        if (i >= size - 1) {
            puts("realloc 1");
						size*=2;
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
        char *key = malloc(KSIZEWORD);
        descriptors[i].p=malloc(size2*sizeof(pile));
        int j=-1;
        while (content[cpt] != '>' && cpt < max) {
            if (file_type==TEXT || file_type==IMAGE){
                int n;
                //printf("line %s\n", line);
                sscanf(&content[cpt], "%s %d", key, &n);

                    while (content[cpt] != '\n') {
                    //putchar(content[cpt]);
                    cpt += 1;
                }
								cpt+=1;
                    //puts("before");
                add_nb_value_hash_map(&(descriptors[i].map), key, n);
                //puts("after");

                //printf("cont %d\n", strlen(content));
                //printf("[%d/%d]%s => %d\n", cpt, max, key, n);
            }
            else if (file_type==SOUND){
                if (j >= size2 - 1) {
                //    puts("realloc 2");
                    size2 *= 2;

                    descriptors[i].p = realloc(descriptors[i].p, sizeof(pile) * size2);
                }
                INIT_PILE( descriptors[i].p[j]);
                int n;
                while (content[cpt] != '\n') {
                        sscanf(&content[cpt], "%d", &n);
                        while (content[cpt]!= ' ') cpt++;
                        EMPILE(&descriptors[i].p[j], n);

                    cpt ++;
                }
                //Remove the newline
                cpt ++;
                j++;
            }

        }
        size ++;
        descriptors[i].p_size=j;
    }
    *size_desc = i;
    return descriptors;
}
int check_descriptor(DataFile df, DataFile *data_files, size_t size) {
	/*
	Check if the descriptor given in parameter is update-to-date according the
	data_files' array (with the size size)
	*/
	if (df.length == 0) {
		puts("no descriptor found !");
		return 1;
	}

	puts("Have to check every file...");
	//  return 1;
	char *content = read_string_from_file(df);

	int size_desc;
	Descriptor *desc = extract_all_descriptor(content, &size_desc);
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
	/*
	Init a descriptor at the path path
	*/
	time_t rawtime = time(NULL);
	Descriptor descriptor = { .map = NULL, .date = rawtime };
	strcpy(descriptor.file_name, path);
	return descriptor;
}


void descriptor_to_file(Descriptor descriptor, DataFile df) {
	/*
	Add a descriptor descriptor at the end of the file df
	*/
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

	free(result);
}

int compare_descriptors(Descriptor desc1, Descriptor desc2) {
	/*
	Compare 2 descriptors without regarding of its type
	*/
	CellHashMap* map1 = desc1.map;
	CellHashMap* map2 = desc2.map;

	int common = 0;
	while (map1 != NULL) {
		while (map2 != NULL) {

			if (!strcmp(map1->key, map2->key)) {
				int min = map1->nbOccurence;
				if (min > map2->nbOccurence) {
					min = map2->nbOccurence;
				}
				common += min;
			}
			map2 = map2->next;
		}
		map2 = desc2.map;
		map1 = map1->next;
	}
	return common;
}


float compare_sound_descriptors( pile* desc1, pile* desc2){// (not tested yet, waiting for descriptor_extractor)
        double tmp, tmp2, moy=0.0;
        int cpt =0;
            cellule* p1 = desc1->tete;
            cellule* p2 = desc2->tete;
            while (p1 != NULL && p2!=NULL) {

                if (p1->element==p2->element) {
                    moy+=1.0;
                }
                else{
                    tmp= (double)p1->element;
                    tmp2= (double)p2->element;
                    if (tmp!=0&&tmp2!=0){
                        if (tmp<tmp2)
                            moy+= tmp/tmp2;
                        if (tmp>tmp2)
                            moy+= tmp2/tmp;
                    }
                }
                cpt++;
                p1 = p1->suivant;
                p2 = p2->suivant;
            }
            if (p1 != NULL)
                while (p1 != NULL){
                    p1 = p1->suivant;
                    cpt++;
                }
        if (moy!=0.0) return (moy/cpt *100);
        return 0.0;
}



void INIT_PILE(pile* p)
{
    p=NULL;
}

void AFFICHE_PILE( pile *p)
{
    cellule *tmp=p->tete;
    while( tmp!=NULL){
        printf("%d ", tmp->element);
        tmp=tmp->suivant;
    }
}

int PILE_EST_VIDE( pile *p)
{
    return (p==NULL);
}

void EMPILE ( pile *p, int val)
{
    cellule *tmp;
    tmp=(cellule*)malloc(sizeof(cellule));
    tmp->element=val;
    tmp->suivant=p->tete;
    p->tete=tmp;
}

int DEPILE (pile *p)
{
    int val;
    cellule * tmp=p->tete;
}
