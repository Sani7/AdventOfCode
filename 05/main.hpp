#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "../libs/quickSort/quickSort.hpp"

#define LINES  500
#define DIM   1000

/*
 * x0, y0 first coordinate
 * x1, y1 seccond coordinate
 * dx, dy direction of travel from x0 or y0
 * (1 == from x0 to x1, 0 is not travelling, -1 is going from x1 to x0)
*/

typedef struct {
    int x0, y0, x1, y1, dx, dy;
    bool diag;
} Line;

int calcFileLength(FILE* fp);
int multivent(bool diag, Line* line, int lines, int vent[][DIM]);
