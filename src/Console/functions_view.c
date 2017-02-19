/*
 ============================================================================
 Name        : main.c
 Author      : Thomas
 Description : Console View of the software
 ============================================================================
 */

#include "functions_view.h"


int login_view(){
	char pass[KPASSLEN];
	puts("Please, enter the password :");
	if (!get_secure_input(pass, sizeof(pass))) {
		puts("Input error");
		return 0;
	}
	else{
		int res = login(pass);
		if (res == -1){
			puts("The password file has not been detected. Password has been reset.");
			return 0;
		}

		else if (res == 0)
			puts("Wrong password : access forbidden !");
		else if (res == 1)
			puts("You are now connected as admin !");
		return res;
	}
}

void display_data_base() {
	/*
	Display every file with the good extension in the databse path
	*/
	DataFile* text_files = get_text_files();
	DataFile* image_files = get_image_files();
	DataFile* sound_files = get_sound_files();
	char* path = get_data_from_config("path");

	printf("Text Files :\n");
	for (int i = 0; i < get_nb_text(); i += 1) {
		printf("\t-%s\n", remove_path(text_files[i].path));
	}

	printf("\nImage Files :\n");
	for (int i = 0; i < get_nb_image(); i += 1) {
		printf("\t-%s\n", remove_path(image_files[i].path));
	}

	printf("\nAudio Files :\n");
	for (int i = 0; i < get_nb_sound(); i += 1) {
		printf("\t-%s\n", remove_path(sound_files[i].path));
	}
}

void update_text_descriptor_view(int force){
	puts("\n\n ==================================================================");
	puts(" >>>    TEXT DESCRIPTOR UPDATE\n");
	printf(" -> Updating text descriptor...");
	int res_txt = update_text_descriptor(force);
	if (res_txt == 0)
		printf("\n -> %d text descriptors already up-to-date !\n", get_nb_text());
	else if (res_txt >= 1)
		printf(" Done !\n -> %d text descriptors updated !\n", get_nb_text());
	if (res_txt == 2)
		puts(" -> Index updated !");
}

void update_image_descriptor_view(int force){
	puts("\n\n ==================================================================");
	puts(" >>>    IMAGE DESCRIPTOR UPDATE\n");
	printf(" -> Updating image descriptor...");
	int res_image = update_image_descriptor(force);
	if (res_image == 0)
		printf("\n -> %d image descriptors already up-to-date !\n", get_nb_image());
	else if (res_image == 1)
		printf(" Done !\n -> %d image descriptors updated !\n", get_nb_image());
}

void update_sound_descriptor_view(int force){
	puts("\n\n ==================================================================");
	puts(" >>>    SOUND DESCRIPTOR UPDATE\n");
	printf(" -> Updating sound descriptor...");
	int res_sound = update_sound_descriptor(force);
	if (res_sound == 0)
		printf("\n -> %d sound descriptors already up-to-date !\n", get_nb_sound());
	else if (res_sound == 1)
		printf(" Done !\n -> %d sound descriptors updated !\n", get_nb_sound());
}

void init_search_engine(){
	puts("\n\n ==================================================================");
	puts(" >>>    SEARCH ENGINE : INITITIALIZATION\n");
	printf(" -> Loading data base...");
	load_data_base();
	printf(" Done !\n");
	printf(" -> %d text file found !\n", get_nb_text());
	printf(" -> %d image file found !\n", get_nb_image());
	printf(" -> %d sound file found !\n", get_nb_sound());
}

void update_descriptors(int force){
	chrono();
	update_text_descriptor_view(force);
	update_image_descriptor_view(force);
	update_sound_descriptor_view(force);

	if(!DEBUG)
		clear_console();

	printf("\n >>>    GENERATING DESCRIPTORS TIME : %ds\n", chrono());
	puts(" >>>    SEARCH ENGINE : READY\n");
}



void search_by_file_view(){
	/*
	* Lance la recherche par un fichier, quel que soit son format
	*/
	char* file_name = malloc(KSIZE);
	char* file_path = malloc(KSIZE * 2);
	strcpy(file_path, get_data_from_config("path"));

	puts("Please, enter a file path : ");
	if (get_secure_input(file_name, KSIZE)) {
		strcat(file_path, file_name);
		char** results = search_data(file_path);
		int flag = atoi(results[0]);
		switch(flag){
			case -3:
			puts("Search aborted : file type not supported !");
			break;

			case -2 :
			puts("Search aborted : file is empty !");
			break;

			case -1:
			puts("Search aborted : file not found !");
			break;

			default:
			for (int i = 1; i <= flag; i++)
				printf("#[%d]  -  %s\n", i, results[i]);
			break;
		}
		
	}
	free(file_name);
	free(file_path);
}
