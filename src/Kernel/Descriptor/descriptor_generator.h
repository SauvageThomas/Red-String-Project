/*
 * descriptor_generator.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../Tools/hash_map.h"
#include "../Data/constant.h"
#include "../Tools/data_handler.h"
#include "../Tools/hash_map.h"

#ifndef DESCRIPTOR_DESCRIPTOR_GENERATOR_H_
#define DESCRIPTOR_DESCRIPTOR_GENERATOR_H_

int check_descriptor(DataFile df, DataFile *data_files, size_t size);
void descriptor_to_file(Descriptor descriptor, DataFile df);
Descriptor init_descriptor(char* path);
int compare_descriptors(Descriptor desc1, Descriptor desc2);
int compare_sound_descriptors( Descriptor desc1, Descriptor desc2);
Descriptor *extract_all_descriptor(char *content, int *size_desc);

#endif /* DESCRIPTOR_DESCRIPTOR_GENERATOR_H_ */
