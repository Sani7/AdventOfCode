#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

#include "../libs/quickSort/quickSort.hpp"

int nCount(FILE* fp);
int residualsum(int target, int* data, int len);
int residualexp(int target, int* data, int len);