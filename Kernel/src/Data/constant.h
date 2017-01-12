/*
 * constant.h
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#ifndef DATA_CONSTANT_H_
#define DATA_CONSTANT_H_

#define DEBUG 1
#define PROD 1
#define TEST 0

typedef struct {
	char** config;
	size_t size;
	size_t size_word;
} Config;

#define KPASSLEN 20
#define KSIZE 255
#define KSIZEWORD 24

#endif /* DATA_CONSTANT_H_ */
