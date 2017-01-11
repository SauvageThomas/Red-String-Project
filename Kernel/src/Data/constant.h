/*
 * constant.h
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#ifndef DATA_CONSTANT_H_
#define DATA_CONSTANT_H_

#define DEBUG 0
#define PROD 1
#define TEST 0

#define EMBED_BREAKPOINT \
    asm("0:"                              \
        ".pushsection embed-breakpoints;" \
        ".quad 0b;"                       \
        ".popsection;")


#define KPASSLEN 20
#define KSIZE 255
#define KSIZEWORD 24

#endif /* DATA_CONSTANT_H_ */
