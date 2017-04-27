#include "image_finder.h"

void find_image(char *quantif, DataFile df) {
	/*
	 Quantify a file df with the quantification quantif
	 */
	size_t n = (size_t) strtol(quantif, (char **) NULL, 10);
	size_t * size = 0;
	size_t *quant_array = quantify_file(n, df, size);
}

size_t *quantify_file(size_t n, DataFile df, size_t *size) {
	/*
	 Quantify a file with the quantification n, the file df
	 */
	//For now we read the txt file
	size_t len = strlen(df.path);
	df.path[len - 1] = 't';
	df.path[len - 2] = 'x';
	df.path[len - 3] = 't';

	df = init_data_file(df.path);

	int height;
	int width;
	int code;

	df.file = fopen(df.path, "r+");
	fscanf(df.file, "%d", &height);
	fscanf(df.file, "%d", &width);
	fscanf(df.file, "%d", &code);

	*size = width * height;

	size_t *quant_array = malloc(sizeof(size_t) * height * width);
	if (quant_array == NULL) {
		fprintf(stderr, "Malloc failed %s\n", strerror(errno));
	}

	int red_pixels[height * width];
	int green_pixels[height * width];

	for (int c = 0; c < code; c += 1) {
		for (int i = 0; i < height * width; i += 1) {
			Pixel p;

			//First channel
			if (c == 0) {
				fscanf(df.file, "%d", &red_pixels[i]);
				if (code == 1) {
					p.red = red_pixels[i];
					p.blue = p.red;
					p.green = p.red;

					size_t q = quantification(p, n);
					quant_array[i] = q;
				}
			} else if (c == 0) { //Second channel
				fscanf(df.file, "%d", &green_pixels[i]);
			} else { //Third channel
				fscanf(df.file, "%d", &p.blue);
				p.red = red_pixels[i];
				p.green = green_pixels[i];

				size_t q = quantification(p, n);
				quant_array[i] = q;
			}
		}
	}

	return quant_array;
}

void int_to_bin_digit(uint8_t in, uint8_t count, uint8_t* out) {
	/*
	 Convert an int into binary
	 */
	unsigned int mask = 1U << (count - 1);
	int i;
	for (i = 0; i < count; i++) {
		out[i] = (in & mask) ? 1 : 0;
		in <<= 1;
	}
}

int exposant(uint8_t *tmp, int *i, int n) {
	/*
	 Internal function
	 */
	int somme = 0;
	for (int cpt = 0; cpt < n; cpt += 1) {
		somme += tmp[cpt] * pow(2, *i);
		*i -= 1;
	}

	return somme;
}

size_t quantification(Pixel pixel, int n) {
	/*
	 Quantify a pixel pixel with the quantification n
	 */
	uint8_t tmp[8];
	int i = 3 * n - 1;
	size_t res = 0;

	int_to_bin_digit(pixel.red, 8, tmp);
	res += exposant(tmp, &i, n);

	int_to_bin_digit(pixel.green, 8, tmp);
	res += exposant(tmp, &i, n);

	int_to_bin_digit(pixel.blue, 8, tmp);
	res += exposant(tmp, &i, n);

	return res;
}
