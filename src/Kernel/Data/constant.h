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
#include "../Tools/map_of_map.h"

#define DEBUG 1
#define PROD 1
#define TEST 0

#include <time.h>

#include "../Tools/hash_map.h"
#include <stdio.h>


#define KPASSLEN 20
#define KSIZE 255
#define KSIZEWORD 26

typedef struct {
	char** config;
	size_t size;
	size_t size_word;
} Config;

typedef struct {
	MapOfMap map;
	char file_name[KSIZE * 2];
	time_t date;
	size_t size;
	size_t nb_maps;
} Descriptor;



#endif /* DATA_CONSTANT_H_ */
