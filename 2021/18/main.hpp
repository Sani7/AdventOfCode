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

#include "../libs/quickSort/quickSort.hpp"

#define LEN(a) ((int)((sizeof(a) / sizeof(*(a)))))

struct fish
{
    int d, n;
}; /* depth, value */

static int explode(void);
static int split(void);
static int score(void);
static void add_str(const char *s);