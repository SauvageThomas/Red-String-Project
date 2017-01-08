/*
 * functions.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#ifndef GUI_FUNCTIONS_H_
#define GUI_FUNCTIONS_H_

#define PASSLEN 20
#define SIZE 255

const int key[] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215,
		48421, 629, 314, 4784, 5102, 914, 213, 316, 145, 78 };

void xor_crypt(char *password);

#endif /* GUI_FUNCTIONS_H_ */
