/*

 * test.c
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#include "minunit.h"
#include <string.h>

#include "../Tools/data_handler.h"

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
	path = "Data/Test/test_read_string_from_file_1";
	result = read_string_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

	expected = "Bla bla bla watch out about \\n \\t \\r";
	path = "Data/Test/test_read_string_from_file_2";
	result = read_string_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

	expected = "This is     a       ><<<> \\ test ! ";
	path = "Data/Test/test_read_string_from_file_3";
	result = read_string_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

}

MU_TEST(test_write_file) {

	expected = "This is a test ! \n";
	path = "Data/Test/test_write_string_from_file";

	write_string_in_file(path, expected);
	result = read_string_from_file(path);


	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

	expected = "Bla bla bla watch out about \\n \\t \\r";

	write_string_in_file(path, expected);
	result = read_string_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

	expected = "This is     a       ><<<> \\ test ! ";

	write_string_in_file(path, expected);
	result = read_string_from_file(path);

	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));

}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_read_file);
	MU_RUN_TEST(test_write_file);
}

void run_all_tests() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT()
	;
}
