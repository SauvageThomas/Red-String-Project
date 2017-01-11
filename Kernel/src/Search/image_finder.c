#include <stdlib.h>
#include <math.h>

#include "image_finder.h"

void find_image(char *quantif, DataFile df) {
	int n = (int) strtol(quantif, (char **) NULL, 10);

	Pixel pixel = { 255, 128, 64 };
	printf("La quantification donne : %d\n", quantification(pixel, n));

	printf("IMAGE FILE\n");
	//TODO: regroup and count all pixels
	//TODO: compare with index and get the similar files 
}

void int_to_bin_digit(uint8_t in, uint8_t count, uint8_t* out) {
	/* assert: count <= sizeof(int)*CHAR_BIT */
	unsigned int mask = 1U << (count - 1);
	int i;
	for (i = 0; i < count; i++) {
		out[i] = (in & mask) ? 1 : 0;
		in <<= 1;
	}
	puts("");
}

int exposant(uint8_t *tmp, int *i) {
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
