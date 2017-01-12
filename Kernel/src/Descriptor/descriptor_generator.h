/*
 * descriptor_generator.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#include "../Tools/data_handler.h"

#ifndef DESCRIPTOR_DESCRIPTOR_GENERATOR_H_
#define DESCRIPTOR_DESCRIPTOR_GENERATOR_H_

int check_descriptors(char* path);
char* generate_descriptor(DataFile df);

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