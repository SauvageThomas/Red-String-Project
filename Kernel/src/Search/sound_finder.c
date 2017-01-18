#include "sound_finder.h"
#include <stdlib.h>
#include <string.h>

/*double ** file_content ( DataFile df, int n, int k){
	df.file=fopen(df.path, "r");
	double ** file_content =(double **)malloc ((df.length/n +1) * sizeof(double*));
	for (int i =0; i< (df.length/n +1); i++) file_content[i] = (double *)calloc(n, sizeof(double));
		if (df.file!=NULL){
			double tmp=0.0;
			int cpt=0, cpt1=0;
			fscanf( df.file, "%le", &tmp);
			for ( int length=0 ;length<df.length; length ++){
				if (length%n==0&&length!=0){cpt1++;cpt=0;}
				file_content[cpt1][cpt]=tmp;
				cpt++;
				fscanf( df.file, "%le", &tmp);
			}
			fclose(df.file);
		}
		else printf("Impossible d'ouvrir le fichier ! ");
	return file_content;
}*/

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

/*void find_sound(DataFile df, char *taille_fenetre, char *nb_barres){
	printf("SOUND FILE\n");
	int n = (int)strtol(taille_fenetre, (char**) NULL, 10);
	int k = (int)strtol(nb_barres, (char**) NULL, 10);
	printf(" %d et %d\n", n, k);
	double ** values =(double **)malloc ((df.length/n+1) * sizeof(double*));
	for (int i =0; i< (df.length/n+1); i++)
		values[i] = (double *)calloc(n, sizeof(double));
	values = file_content(df, n);
	//for (int i =0; i< (df.length/n+1); i++)
	//	for (int j=0; j<n; j++) printf("%le\n", values[i][j]);
	//TODO: regroup and count all pixels
	//TODO: compare with index and get the similar files
}*/

/*
int main(){
	DataFile df;
	df.path="res/FICHIER_PROJET/jingle_m6.txt";
	df.length=41788;
	find_sound( df, "500", "250");
	return 0;
}
*/
