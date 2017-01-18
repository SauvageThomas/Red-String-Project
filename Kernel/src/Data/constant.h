/*
 * constant.h
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#ifndef DATA_CONSTANT_H_
#define DATA_CONSTANT_H_

#include <time.h>
#include "../Tools/hash_map.h"

#define DEBUG 0
#define PROD 1
#define TEST 0

typedef struct {
	char** config;
	size_t size;
	size_t size_word;
} Config;

typedef struct {
	HashMap map;
	char *file_name;
	struct tm *time;
	size_t size;
} Descriptor;

#define KPASSLEN 20
#define KSIZE 255
#define KSIZEWORD 26

#endif /* DATA_CONSTANT_H_ */
