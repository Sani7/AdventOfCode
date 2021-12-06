#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "../../libs/quickSort/quickSort.hpp"

int calcFileLength(FILE* fp);

void readFile(FILE* in, int* out, int len);
int strToInt(char * str);
int mostCommonBit(int* num, int len, int bit);
int SumToInt(int* list, int len, int alpha);