/*
 ============================================================================
 Name        : functions.c
 Author      : Thomas
 Description : Controller of the software
 ============================================================================
 */

#include "functions.h"

int login(char* password){
	return try_login(password);
}


char** search_data(char* file_path) {
	/*
	Read the configuration config and search the closer result with the file file_path
	*/
	DataFile df = init_data_file(file_path);
	HashMap result = NULL;
	char** results = malloc(6 * sizeof(char*));
	results[0] = malloc(2); //flag
	puts(file_path);
	if (!is_existing_file(df)) {
		sprintf(results[0], "%d", -1);
		return results;
	}
	if (is_empty_file(df)) {
		sprintf(results[0], "%d", -2);
		return results;
	}
	enum FileType file_type = get_data_file_extension(df.path);

	char full_path[KSIZE * 2];
	strcpy(full_path, get_data_from_config("descriptors"));

	switch (file_type) {
	case TEXT:
		strcat(full_path, "text_descriptors");
		break;
	case IMAGE:
		strcat(full_path, "image_descriptors");
		break;
	case SOUND:
		strcat(full_path, "sound_descriptors");
		break;

	default:
		sprintf(results[0], "%d", -3);
		return results;
	}

	df = init_data_file(full_path);

	char *content = read_string_from_file(df);
	int size_desc;
	Descriptor * desc;
	if (file_type == SOUND)
		desc = extract_all_descriptors(content, &size_desc, file_type);
	else
		desc = extract_all_descriptor(content, &size_desc);
	int cpt = 0;
	while (strcmp(desc[cpt].file_name, file_path)) {
		cpt += 1;
	}
	Descriptor descriptor = desc[cpt];
	int i;

	for (i = 0; i < size_desc; i += 1) {
		if (i != cpt) {
			int common = 0;
			float common2 = 0.0;
			// we need to compare every window until one of the two files doesn't have one anymore
			if(file_type == SOUND){
				int counter = 0;
				int k = 0;
				float test = 0.0, moy = 0.0, moy2 = 0.0;
				for (int j = 0; j<descriptor.p_size && j<desc[i].p_size; j++ ){
					moy = compare_sound_descriptors(&descriptor.p[j], &desc[i].p[j]);
					test = compare_sound_descriptors(&descriptor.p[0], &desc[i].p[j]);

					if (test >= 70) {
						int verif = 1;
						if (k >= descriptor.p_size || k>2)
							k--;
						else{
							for (k = 0; k < descriptor.p_size && verif; k++) {
								moy2 = compare_sound_descriptors(&descriptor.p[k], &desc[i].p[j+k]);
								if ( moy2 <= 70) verif = 0;
							}
							if (k >= descriptor.p_size){
								counter++;
							}
						}
					}
					common2 = common2 + moy;
				}
			 /*	if ( descriptor.p_size<desc[i].p_size){
					int counter2 = 0;
					for (;k<desc[i].p_size; k++){
						float	moy2 = compare_sound_descriptors(&descriptor.p[counter2], &desc[i].p[k]);
						if (moy2 == 100){
							while (moy2 == 100){
								counter2++;
								moy2 = compare_sound_descriptors(&descriptor.p[counter2], &desc[i].p[k]);
							}
							if (counter2 >= descriptor.p_size){
								counter++;
							}
						}
					}
				}*/
				// common2 /= descriptor.p_size;
				// else common2 /= desc[i].p_size;
				int trans[1];
				sprintf (trans, "%d", counter);
				strcat(desc[i].file_name,	trans);
				common= (int)common2;

			}
			else
				common = compare_descriptors(descriptor, desc[i]);

			add_nb_value_hash_map(&result, desc[i].file_name, common);
		}

	}
	i-=1;
	int max = 5;
	if (i < max) {
		max = i;
	}
	sprintf(results[0], "%d", max);
	for (int i = 1; i <= max; i += 1) {
		char *tmp = pop_value_hash_map(&result);
		results[i] = malloc(strlen(tmp));
		strcpy(results[i], tmp);
	}
	return results;
}

int update_text_descriptor(int force){
	return check_text_descriptor(force);
}

int update_image_descriptor(int force){
	return check_image_descriptor(force);
}

int update_sound_descriptor(int force){
	return check_sound_descriptor(force);
}


void search_by_keywords_view(){
	puts("Please, enter your keywords (max 10), put \"0\" to stop : ");
	int count = 0;
	char** keywords = malloc(11 * sizeof(char*));
	do{
		char* buffer = malloc(KSIZEWORD);
		get_secure_input(buffer, KSIZEWORD);
		if (!strcmp(buffer, "0")){
			break;
		}
		count ++;
		keywords[count] = malloc(sizeof(buffer));
		strcpy(keywords[count], buffer);
	}while (count < 11);
	sprintf(keywords[0], "%d", count);
	if (!DEBUG)
		clear_console();
	printf("TOTAL KEYWORD(S) : %s\n", keywords[0]);
	for (int i = 1; i <= count; i++)
		printf(" -  %s\n", keywords[i]);
	char** results = search_by_keywords(keywords);

	int flag = atoi(results[0]);
	if (flag == -1)
		puts("No result found !");
	else{
		printf("%s result(s) found ! \n", results[0]);
		for(int i = 1; i <= flag; i++)
			printf(" # [%d]  -  %s\n", i, results[i]);
	}

}

char** search_by_keywords(char** keywords) {
	/*
	Allow the user to search a file using a keyword
	*/

	char* path = get_data_from_config("descriptors");
	char* file_path = malloc(KSIZE * 2);
	strcpy(file_path, path);

	strcat(file_path, "text_index");

	DataFile df = init_data_file(file_path);

	char *content = read_string_from_file(df);

	int length = strlen(content);
	int found = 0;
	int cpt = 0;
	char** results = malloc(6 * sizeof(char*));
	results[0] = malloc(2); // flag
	for (int i = 0; i < length; i += 1) {
		if (content[i] == '>') {
			char *tmp = malloc(KSIZEWORD);
			i += 1;
			sscanf(&content[i], "%s", tmp);
			if (!strcmp(tmp, keywords[1])) {
				found = 1;
				i += strlen(keywords[1]) + 1;
			}
		} else if (found) {
			char *final_string = malloc(2 * KSIZE);
			while (content[i] != '>') {

				if (content[i] == '\n') {
					final_string = pretty_print_string(final_string);
					cpt ++;
					results[cpt] = malloc(strlen(final_string));
					strcpy(results[cpt], final_string);
					strcpy(final_string, "\0");
					if (cpt > 5) {
						break;
					}
				}
				//putchar(content[i]);
				else{
					strncat(final_string, &content[i], 1);
				}
				i += 1;

			}
			sprintf(results[0], "%d", cpt);
			break;
		}
	}
	if (!found) {
		sprintf(results[0], "%d", -1);
	}

	return results;
}
