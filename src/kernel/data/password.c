#include "password.h"

const int pass_key[] = { 22, 53, 44, 71, 66, 177, 253, 122, 9548, 1215, 48421,
		629, 314, 4784, 5102, 914, 213, 316, 145, 78 };

void xor_crypt(char *password) {
	/*
	Crypt an input (modify the input)
	*/
	for (int i = 0; i < KPASSLEN; i += 1) {
		password[i] ^= pass_key[i];
	}
}

void change_password() {
	/*
	Allow an admin to change his password
	*/
	char pass[KPASSLEN];
	puts("Please, enter the password :");
	get_secure_input(pass, sizeof(pass));

	DataFile data_file = init_data_file(".pass");

	xor_crypt(pass);
	write_string_in_file(data_file, pass);
	puts("Password correctly changed !");
}

int try_login(char* password) {
	/*
	Allow a user to connect as an admin
	*/
	int res = 0;
	DataFile data_file = init_data_file(".pass");

	if (data_file.length == 0) { //The file is empty or does not exist
		strcpy(password, "admin");
		xor_crypt(password);
		write_string_in_file(data_file, password);
		return -1;
	}

	char* compare = read_string_from_file(data_file);

	xor_crypt(compare);

	if (!strcmp(compare, password))
		res = 1;
	free_data_file(data_file);
	return res;
	
}