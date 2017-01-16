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

int check_descriptors(DataFile df);
Descriptor generate_descriptor(DataFile df, int quant);
void descriptor_to_file(Descriptor descriptor, DataFile df);
void generate_text_descriptors(DataFile df, Directory dir);
void generate_image_descriptors(DataFile df, Directory dir, int quant);
void generate_sound_descriptors(DataFile df, Directory dir);

#endif /* DESCRIPTOR_DESCRIPTOR_GENERATOR_H_ */




/*
pu abs class El <T > implements Comparable<El<T>>{
	private T value;

	El(T value){
		this.value = value;
	}

	T getValue(){
		return this.value;
	}

	void setValue(T value){
		this.value = value;
	}

	@Override 
	public int compareTo(Element other){
		return this.value.compareTo(other.value);
	}

pu class ElInt extends El<Integer> {

} 

pu class ElChaine extends El<String> {

}*/
