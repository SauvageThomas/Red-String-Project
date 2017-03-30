/*
 * constant.h
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#ifndef DATA_CONSTANT_H_
#define DATA_CONSTANT_H_

#include <stdio.h>
#include <time.h>

#include "../tools/map_of_map.h"

#define DEBUG 0
#define PROD 1
#define TEST 0

#define KPASSLEN 20
#define KSIZE 255
#define KSIZEWORD 26

#if (defined(_WIN32) || defined(_WIN64))
#define OS 1
#else
#define OS 0
#endif

typedef struct cellule{
	struct cellule * suivant;
	int element;
} cellule;

typedef struct pile{
	cellule * tete;
}pile;

typedef struct {
	MapOfMap map;
	char file_name[KSIZE * 2];
	time_t date;
	size_t size;
	size_t nb_maps;
	pile *p;
	size_t p_size;
	size_t nb_intervalles;
} Descriptor;

#endif /* DATA_CONSTANT_H_ */
