#include <stdlib.h>
#include <math.h>

#include "image_finder.h"

void find_image(char *quantif, DataFile df) {
	int n = (int) strtol(quantif, (char **) NULL, 10);

	size_t size = 2;
	Pixel *pixels = malloc(sizeof(Pixel) * size);
	Pixel pixel = { 255, 128, 64 };
	pixels[0] = pixel;
	Pixel pixel2 = { 64, 234, 18 };
	pixels[1] = pixel2;

	for (int i = 0; i < size; i += 1) {
		int q = quantification(pixels[i], n);
		printf("La quantification donne : %d\n", q);
	}
	printf("IMAGE FILE\n");
	//TODO: regroup and count all pixels
	//TODO: compare with index and get the similar files 
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

int exposant(uint8_t *tmp, int *i) {
	//printf("%d %d\n", tmp[0], tmp[1]);
	*i -= 2;
	return tmp[0] * pow(2, *i + 2) + tmp[1] * pow(2, *i + 1);
}

int quantification(Pixel pixel, int n) {
	uint8_t tmp[8];
	int i = 5;
	int res = 0;

	int_to_bin_digit(pixel.red, 8, tmp);
	res += exposant(tmp, &i);

	int_to_bin_digit(pixel.green, 8, tmp);
	res += exposant(tmp, &i);

	int_to_bin_digit(pixel.blue, 8, tmp);
	res += exposant(tmp, &i);

	return res;
}
