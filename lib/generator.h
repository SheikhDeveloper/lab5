#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voters.h"

Array gen_arr(size_t size);
Elector *gen_struc();
char *gen_name();
char gen_char();
char gen_letter();
char gen_digit();
int gen_age();

#endif
