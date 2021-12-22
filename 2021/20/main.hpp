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
#include <inttypes.h>
#include <assert.h>

#include "../libs/quickSort/quickSort.hpp"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SZ 210
#define X0 55
#define Y0 55

static void step(void);
static int count_on(void);