#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "../libs/quickSort/quickSort.hpp"

#define LINES  500
#define DIM   1000

typedef struct {
    int x0, y0, x1, y1, dx, dy;
    bool diag;
} Line;

int multivent(bool diag, Line* line, int vent[][DIM]);
