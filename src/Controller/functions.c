/*
 ============================================================================
 Name        : functions.c
 Author      : Thomas
 Description : Controller of the software
 ============================================================================
 */

#include "functions.h"

int search_data(char* file_path) {
	/*
	Read the configuration config and search the closer result with the file file_path
	*/
	DataFile df = init_data_file(file_path);
	HashMap result = NULL;

	if (!is_existing_file(df)) {
		return FILE_NOT_FOUND;
	}

	if (is_empty_file(df)) {
		return EMPTY;
	}

	enum FileType file_type = get_data_file_extension(df.path);

	char full_path[KSIZE * 2];
	strcpy(full_path, get_value_of("descriptors"));

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
		return FILE_TYPE_NOT_SUPPORTED;
		break;
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
	puts("\n\nSame file type scores :\n");
	Descriptor descriptor = desc[cpt];
	int i;

	for (i = 0; i < size_desc; i += 1) {
		if (i != cpt) {
			int common = 0;
			float common2 = 0.0;
			// we need to compare every window until one of the two files doesn't have one anymore
			if(file_type == SOUND){
				float moy=0.0;
				for (int j=0; j<descriptor.p_size && j<desc[i].p_size; j++ ){
					moy = compare_sound_descriptors(&descriptor.p[j], &desc[i].p[j]);
					common2 = common2 + moy;
				}
				// if ( descriptor.p_size>desc[i].p_size)
				// common2 /= descriptor.p_size;
				// else common2 /= desc[i].p_size;
				common= (int)common2;
			}
			else
				common = compare_descriptors(descriptor, desc[i]);

			add_nb_value_hash_map(&result, desc[i].file_name, common);
		}

	}
	int max = 5;
	if (i < max) {
		max = i-1;
	}

	for (int i = 0; i < max; i += 1) {
		// puts("passed ! \n");
		char *tmp = pop_value_hash_map(&result);

		if (i==0){

			char c = tmp[0];

			int count = 0;
			char *file = malloc(strlen(tmp));

			file[0] = '\0';
			while(c != ' '){
				c = tmp[count];
				strncat(file, &c, 1);

				count += 1;
			}
			//printf("\nBEST RESULT : %s\n\n", file);
			display_rank(file, 1);
			char* cmd = malloc(KSIZE);
			sprintf(cmd, "%s%s%s", "xdg-open ", file, " &");
			printf("\n>> open the best result with : %s\n", cmd);
			system(cmd);
		}

		//Change the content of the string
		char *final_string;
		switch (file_type) {
		case TEXT:
			final_string = pretty_print_string(tmp);
			break;
		case IMAGE:
			final_string = pretty_print_image(tmp);
			break;
		case SOUND:
			final_string = pretty_print_sound(tmp);
			break;
		}
		display_rank(final_string, i+1);
		//printf("\n* RANK [%d] : %s", (i+1), final_string);
	}
	return SUCCESS;
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

void search_by_keyword(char *path) {
	/*
	Allow the user to search a file using a keyword
	*/
	puts("Please, enter a unique key word : ");

	char *keyword = malloc(KSIZEWORD);
	get_secure_input(keyword, KSIZE);

	char* file_path = malloc(KSIZE * 2);
	strcpy(file_path, path);

	strcat(file_path, "text_index");

	DataFile df = init_data_file(file_path);

	char *content = read_string_from_file(df);

	int length = strlen(content);
	int found = 0;
	int cpt = 0;
	puts("Result :");
	for (int i = 0; i < length; i += 1) {
		if (content[i] == '>') {
			char *tmp = malloc(KSIZEWORD);
			i += 1;
			sscanf(&content[i], "%s", tmp);
			//printf("<%s> <%s>\n", tmp, keyword);
			if (!strcmp(tmp, keyword)) {

				//puts("Ok");
				found = 1;
				i += strlen(keyword) + 1;
			}
		} else if (found) {
			char *final_string = malloc(KSIZEWORD * 45);
			while (content[i] != '>') {

				if (content[i] == '\n') {
					if (cpt > 5) {
						break;
					}
					final_string = pretty_print_string(final_string);
					printf("%s\n", final_string);
					strcpy(final_string, "");
					cpt += 1;
				}
				//putchar(content[i]);
				strncat(final_string, &content[i], 1);
				i += 1;

			}
			break;
			exit(0);
		}
	}
	if (!found) {
		puts("No result found");
	}
}

time_t chrono() {
	/*
	The first call create the chrono (you should not use the outpout)
	and the second call return the time between the first and the second call
	*/
	static time_t prev_time;
	time_t res = time(NULL) - prev_time;
	prev_time = time(NULL);
	return res;
}
