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
char *TEST_WRITE_FILE_PATH = "Data/Test/test_write_string_from_file";


void test_setup() {
	puts("\n\n---------------------------- TEST ----------------------------");
	strcpy(msg, "EXPECTED : ");
}

void test_teardown() {
	puts("\n---------------------------- DONE ----------------------------\n");
}

void assert_equals_str(char* expected, char* result){
	printf("EXPECTED LENGTH : %d\n", strlen(expected));
	printf("EXPECTED VALUE  : %s\n\n", expected);
	printf("RESULT LENGTH   : %d\n", strlen(result));
	printf("RESULT VALUE    : %s\n", result);
	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));
}

MU_TEST(test_read_file_1) {
	char* expected = "This is a test ! \n";
	char* path = "Data/Test/test_read_data_from_file_1";
	char* result = read_string_from_file(path);
	assert_equals_str(expected, result);
}

MU_TEST(test_read_file_2) {
	char *expected = "Bla bla bla watch out about \\n \\t \\r";
	char *path = "Data/Test/test_read_data_from_file_2";
	char *result = read_string_from_file(path);
	assert_equals_str(expected, result);
}

MU_TEST(test_read_file_3) {
	char *expected = "This is     a       ><<<> \\ test !";
	char *path = "Data/Test/test_read_data_from_file_3";
	char *result = read_string_from_file(path);
	assert_equals_str(expected, result);
}

MU_TEST(test_write_file_1) {
	char *expected = "This is a test ! \n";
	write_string_in_file(TEST_WRITE_FILE_PATH, expected);
	char *result = read_string_from_file(TEST_WRITE_FILE_PATH);
	assert_equals_str(expected, result);
}

MU_TEST(test_write_file_2) {
	char *expected = "Bla bla bla watch out about \\n \\t \\r";
	write_string_in_file(TEST_WRITE_FILE_PATH, expected);
	char *result = read_string_from_file(TEST_WRITE_FILE_PATH);
	assert_equals_str(expected, result);
}

MU_TEST(test_write_file_3) {
	char *expected = "This is     a       ><<<> \\ test ! ";
	write_string_in_file(TEST_WRITE_FILE_PATH, expected);
	char *result = read_string_from_file(TEST_WRITE_FILE_PATH);
	assert_equals_str(expected, result);
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_read_file_1);
	MU_RUN_TEST(test_read_file_2);
	MU_RUN_TEST(test_read_file_3);
	MU_RUN_TEST(test_write_file_1);
	MU_RUN_TEST(test_write_file_2);
	MU_RUN_TEST(test_write_file_3);
}

void run_all_tests() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
}
