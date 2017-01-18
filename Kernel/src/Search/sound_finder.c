#include "sound_finder.h"
#include <stdlib.h>
#include <string.h>

int compare_2_sounds(){
	int score = 0;
	return score;
}

HashMap file_content (DataFile df, int size_window, int nb_intervalles){
	HashMap soundMap = malloc(sizeof(CellHashMap) * size_window);
	df.file=fopen(df.path, "rb");
		if (df.file!=NULL){
		double value;
			for (size_t i = 0; i < df.length/sizeof(double); i++){
				fread(&value,sizeof(double),1,df.file);
				init_hash_map(&soundMap[i/size_window]);
				histogramme(soundMap[i/size_window], value, nb_intervalles);
			}
			fclose(df.file);
		}
		else printf("Impossible d'ouvrir le fichier ! ");
	return soundMap;
}

CellHashMap histogramme(CellHashMap hist, double valeur, int nb_intervalles){
		size_t check = 0;
		int count = 0;
		char str[4];
		while (check == 0) {
			if (valeur < -1+(2/(double)nb_intervalles)*count) {
				sprintf(str, "%d", count);
				add_value_hash_map(&hist, str);
				check = 1;
			} else {
				count += 1;
			}
		}
	return hist;
}
