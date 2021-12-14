#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <err.h>

#include "../libs/quickSort/quickSort.hpp"

void count_template(const char* input, long* nb_pairs);
void execute_step(long* nb_pairs, const int* insertions);
void run(FILE* datafile, FILE* output, int nb_steps);