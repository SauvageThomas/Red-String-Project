#include "sound_finder.h"

int compare_2_sounds(){
	int score = 0;
	return score;
}

int *file_content (DataFile df, int size_window, int nb_intervalles, size_t *count_maps){
	*count_maps = (df.length/sizeof(double) + (size_window-1)) / size_window;

	int* sound_values = malloc((df.length/sizeof(double))*sizeof(int));
	df.file=fopen(df.path, "rb");
		if (df.file!=NULL){
		double value;
			for (int i = 0; i < df.length/sizeof(double); i++){
				fread(&value,sizeof(double),1,df.file);
				sound_values[i] = histogramme(value, nb_intervalles);
			}
			fclose(df.file);
		}
		else printf("Impossible d'ouvrir le fichier ! ");

	return sound_values;
}

int histogramme(double valeur, int nb_intervalles){
		int count = 0;
		while (1) {
			if (valeur < -1+(2/(double)nb_intervalles)*count) {
				return count;
			} else {
				count += 1;
			}
		}
}
