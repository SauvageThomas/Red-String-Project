

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "constant.h"
#include "../Tools/data_handler.h"

void error_config_file();
void modif_config();
void reset_config();
void init_config();
void load_config();
char* get_value_of(const char* value);