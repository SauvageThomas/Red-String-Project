/*
 * image_finder.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#ifndef SEARCH_IMAGE_FINDER_H_
#define SEARCH_IMAGE_FINDER_H_

#include "../Tools/data_handler.h"
#include <stdint.h>

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} Pixel;

void int_to_bin_digit(uint8_t in, uint8_t count, uint8_t* out);
int exposant(uint8_t *tmp, int *i, int n);
size_t quantification(Pixel pixel, int n);
void find_image(char *quantification, DataFile df);
size_t *quantify_file(size_t n, DataFile df, size_t *size);

#endif /* SEARCH_IMAGE_FINDER_H_ */
