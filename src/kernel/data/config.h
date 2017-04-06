

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "constant.h"
#include "../tools/data_handler.h"

void error_config_file();
void modif_config();
void reset_config();
void init_config();
void load_config();
char* get_data_from_config(const char* value);
