/*
 * descriptor_generator.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#include "../Tools/data_handler.h"
#include "../Data/constant.h"

#ifndef DESCRIPTOR_DESCRIPTOR_GENERATOR_H_
#define DESCRIPTOR_DESCRIPTOR_GENERATOR_H_

<<<<<<< HEAD
int check_descriptor(DataFile df, DataFile *data_files, size_t size);
=======
int check_files();
int check_descriptor(DataFile df);
>>>>>>> branch 'dev' of https://github.com/SauvageThomas/Red-String-Project.git
Descriptor generate_descriptor(DataFile df, int quant);
void descriptor_to_file(Descriptor descriptor, DataFile df);
Descriptor init_descriptor(char* path);

#endif /* DESCRIPTOR_DESCRIPTOR_GENERATOR_H_ */
