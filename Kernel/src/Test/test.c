/*
 * test.c
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#include "minunit.h"
#include <string.h>

#include "../Tools/tools.h"

char msg[50];
char *expected;
char *path;
char *result;

void test_setup() {
	strcpy(msg, "Should be : ");
}

void test_teardown() {
	/* Nothing */
}

MU_TEST(test_read_file) {

	expected = "This is a test ! \n";
	path = "Data/Test/test_read_data_from_file_1";
	result = read_data_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

	expected = "Bla bla bla watch out about \\n \\t \\r";
	path = "Data/Test/test_read_data_from_file_2";
	result = read_data_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

	expected = "This is     a       ><<<> \\ test ! ";
	path = "Data/Test/test_read_data_from_file_3";
	result = read_data_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_read_file);
}

void run_all_tests() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT()
	;
}
