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

int sintersect(const char *s1, const char *s2);
int cmp_char(const void *p1, const void *p2);
int cmp_len(const void *p1, const void *p2);
int cmp_magic(const void *p1, const void *p2);