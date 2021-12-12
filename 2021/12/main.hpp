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

#define maxSize 1000

// DFS implementations
#define START_NODE 0
#define END_NODE 1


int getID(char *str);
int makeID(char *str);
void dfs(int from, int *pathCntPtr);
void dfs2(int from, int *pathCntPtr, int* wildcard);