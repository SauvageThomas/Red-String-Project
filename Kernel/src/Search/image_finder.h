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

void find_sound(DataFile df);
int quantification(Pixel pixel, int n);
void find_image(char *quantification, DataFile df);

#endif /* SEARCH_IMAGE_FINDER_H_ */
