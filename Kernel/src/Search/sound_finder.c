#include "sound_finder.h"
#include <stdlib.h>
#include <string.h>

double ** file_content ( DataFile df, int n, int k){
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
}
void find_sound(DataFile df, char *taille_fenetre, char *nb_barres){
	printf("SOUND FILE\n");
	int n = (int)strtol(taille_fenetre, (char**) NULL, 10);
	int k = (int)strtol(nb_barres, (char**) NULL, 10);
	printf(" %d et %d\n", n, k);
	double ** values =(double **)malloc ((df.length/n+1) * sizeof(double*));
	for (int i =0; i< (df.length/n+1); i++) values[i] = (double *)calloc(n, sizeof(double));
	values = file_content(df, n, k);
	//for (int i =0; i< (df.length/n+1); i++)
	//	for (int j=0; j<n; j++) printf("%le\n", values[i][j]);
	//TODO: regroup and count all pixels
	//TODO: compare with index and get the similar files 
}

	
}
			
int main(){
	DataFile df;
	df.path="/home/michael/Red-String-Project/Kernel/res/FICHIER_PROJET/jingle_m6.txt";
	df.length=41788;
	find_sound( df, "500", "250");
	return 0;
}

