#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>

#include "../libs/quickSort/quickSort.hpp"

#define CYCLE 7
#define DELAY 2
#define LIFE  (CYCLE + DELAY)
#define DAYS1 80
#define DAYS2 256

uint64_t live(uint64_t* pop, int birth, int days);