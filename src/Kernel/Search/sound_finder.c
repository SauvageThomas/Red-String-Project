#include "sound_finder.h"

int compare_2_sounds(){
	int score = 0;
	return score;
}

MapOfMap file_content (DataFile df, int size_window, int nb_intervalles, size_t *count_maps){
	MapOfMap soundMap;
	init_MapOfMap(&soundMap);
	*count_maps = (df.length/sizeof(double) + (size_window-1)) / size_window;
	df.file=fopen(df.path, "rb");
	if (df.file!=NULL){
		double value;
		for (int i = 0; i < df.length/sizeof(double); i++){
			fread(&value,sizeof(double),1,df.file);
			printf("%d\n", value);
			histogramme(&soundMap, (int)floor((i+1)/(double)size_window), value, nb_intervalles);
		}
		puts("OK");
		fclose(df.file);
	}
	else printf("Impossible d'ouvrir le fichier ! ");

	return soundMap;
}

void histogramme(MapOfMap* hist, int fenetre, double valeur, int nb_intervalles){
		size_t check = 0;
		int count = 0;
		char str[10];
		char str2[10];
		sprintf(str2, "%d", fenetre);
		while (check == 0) {
			puts("OK");
			if (valeur < -1+(2/(double)nb_intervalles)*count) {
				sprintf(str, "%d", count);
				add_value_MapOfMap(hist, str2, str, 1);
				check = 1;
			} else {
				count += 1;
			}
		}
}
