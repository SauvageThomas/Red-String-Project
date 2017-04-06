/*

 * test.c
 *
 *  Created on: 17 nov. 2016
 *      Author: THOMAS
 */

#include "minunit.h"
#include <string.h>

#include "../tools/data_handler.h"
#include "../tools/hash_map.h"

char msg[50];
char *TEST_WRITE_FILE_PATH = "src/Data/Test/test_write_string_from_file";
int test_num = 1;

void test_setup() {
	printf("\n\n-------------------------- TEST %d ----------------------------\n",	test_num);
	strcpy(msg, "EXPECTED : ");
}

void test_teardown() {
	puts("\n-------------------------- DONE -------------------------------\n");
	test_num++;
}

void assert_equals_str(char* expected, char* result) {
	printf("EXPECTED LENGTH : %d\n", strlen(expected));
	printf("EXPECTED VALUE  : %s\n\n", expected);
	printf("RESULT LENGTH   : %d\n", strlen(result));
	printf("RESULT VALUE    : %s\n", result);
	mu_assert(strcmp(expected, result) == 0, strcat(msg, expected));
}

MU_TEST(test_read_file_1) {
	char* expected = "This is a test ! \n";
	char* path = "src/Data/Test/test_read_data_from_file_1";
	DataFile df = init_data_file(path);
	char* result = read_string_from_file(df);
	assert_equals_str(expected, result);
}

MU_TEST(test_read_file_2) {
	char *expected = "Bla bla bla watch out about \\n \\t \\r";
	char *path = "src/Data/Test/test_read_data_from_file_2";
	DataFile df = init_data_file(path);
	char* result = read_string_from_file(df);
	assert_equals_str(expected, result);
}

MU_TEST(test_read_file_3) {
	char *expected = "This is     a       ><<<> \\ test !";
	char *path = "src/Data/Test/test_read_data_from_file_3";
	DataFile df = init_data_file(path);
	char* result = read_string_from_file(df);
	assert_equals_str(expected, result);
}

MU_TEST(test_write_file_1) {
	char *expected = "This is a test ! \n";
	DataFile df = init_data_file(TEST_WRITE_FILE_PATH);
	write_string_in_file(df, expected);
	char* result = read_string_from_file(df);
	assert_equals_str(expected, result);
}

MU_TEST(test_write_file_2) {
	char *expected = "Bla bla bla watch out about \\n \\t \\r";
	DataFile df = init_data_file(TEST_WRITE_FILE_PATH);
	write_string_in_file(df, expected);
	char* result = read_string_from_file(df);
	assert_equals_str(expected, result);
}

MU_TEST(test_write_file_3) {
	char *expected = "This is     a       ><<<> \\ test !";
	DataFile df = init_data_file(TEST_WRITE_FILE_PATH);
	write_string_in_file(df, expected);
	char* result = read_string_from_file(df);
	assert_equals_str(expected, result);
}

MU_TEST(test_hash_map_1) {
	//HashMap map = malloc(sizeof(HashMap));
	//init(&map);
	//addValue(&map, "Test", 2);
	//TODO pas assez de méthode pour tester la fonctionnalité

}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_read_file_1);
	MU_RUN_TEST(test_read_file_2);
	MU_RUN_TEST(test_read_file_3);
	MU_RUN_TEST(test_write_file_1);
	MU_RUN_TEST(test_write_file_2);
	MU_RUN_TEST(test_write_file_3);
	MU_RUN_TEST(test_hash_map_1);
}

void run_all_tests() {
	puts("Running tests ...\n");
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	puts("tests done !");
}
