#include <stdlib.h>
#include <math.h>
#include <errno.h>

#include "image_finder.h"
#include "../GUI/functions.h"

void find_image(char *quantif, DataFile df) {
	if (quantif == NULL) {
		error_config_file();
	}
	size_t n = (size_t) strtol(quantif, (char **) NULL, 10);
	size_t size;
	int *quant_array = quantify_file(n, df, size);

	//TODO: compare with index and get the similar files 
}

size_t *quantify_file(size_t n, DataFile df, size_t *size) {

	//For now we read the txt file
	size_t len = strlen(df.path);
	df.path[len - 1] = 't';
	df.path[len - 2] = 'x';
	df.path[len - 3] = 't';

	df = init_data_file(df.path);

	//char *content = read_string_from_file(df);
	int height;
	int width;
	int code;

	//printf("%s\n", content);

	df.file = fopen(df.path, "r+");
	fscanf(df.file, "%d", &height);
	fscanf(df.file, "%d", &width);
	fscanf(df.file, "%d", &code);

	*size = width * height;

	printf("%d %d %d\n", height, width, code);

	/*Pixel *pixels = malloc(sizeof(Pixel) * height * width);
	if (pixels == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}*/

	size_t *quant_array = malloc(sizeof(size_t) * height * width);
	if (quant_array == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}
	puts("loop");
	for (int i = 0; i < height * width; i += 1) {
		Pixel p;
		fscanf(df.file, "%d", &p.red);
		fscanf(df.file, "%d", &p.green);
		fscanf(df.file, "%d", &p.blue);

		size_t q = quantification(p, n);
		//printf("r :%d\n", pixels[i].red);
		quant_array[i] = q;
		//printf("Quant : %d\n", q);
	}
	/*
	puts("Free");
	free(pixels);*/
	return quant_array;

	/* Exemple
	 size_t size = 2;
	 Pixel pixel = { 255, 128, 64 };
	 pixels[0] = pixel;
	 Pixel pixel2 = { 64, 234, 18 };
	 pixels[1] = pixel2;


	 for (int i = 0; i < size; i += 1) {
	 int q = quantification(pixels[i], n);
	 printf("La quantification donne : %d\n", q);
	 }*/
}

void int_to_bin_digit(uint8_t in, uint8_t count, uint8_t* out) {
	unsigned int mask = 1U << (count - 1);
	int i;
	for (i = 0; i < count; i++) {
		out[i] = (in & mask) ? 1 : 0;
		//printf("%d",out[i]);
		in <<= 1;
	}
	//puts("");
}

int exposant(uint8_t *tmp, int *i, int n) {
	//printf("%d %d\n", tmp[0], tmp[1]);
	int somme = 0;
	for (int cpt = 0; cpt < n; cpt += 1) {
		somme += tmp[cpt] * pow(2, *i);
		*i -= 1;
	}

	return somme;
}

size_t quantification(Pixel pixel, int n) {
	uint8_t tmp[8];
	int i = 5;
	size_t res = 0;

	int_to_bin_digit(pixel.red, 8, tmp);
	res += exposant(tmp, &i, n);

	int_to_bin_digit(pixel.green, 8, tmp);
	res += exposant(tmp, &i, n);

	int_to_bin_digit(pixel.blue, 8, tmp);
	res += exposant(tmp, &i, n);

	return res;
}
