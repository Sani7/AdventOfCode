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

#define STEPS 100
#define FLASH 10
#define DIM 10

int cascade(int lum[DIM + 2][DIM + 2], bool flashed[DIM + 2][DIM + 2]);
bool all(bool flashed[DIM + 2][DIM + 2]);