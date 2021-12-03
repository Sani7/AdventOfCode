#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "../../libs/quickSort/quickSort.hpp"

typedef struct
{
    int zeros = 0;
    int ones = 0;
}Element;

typedef struct
{
    Element E[12];
} Elements;

int calcFileLength(FILE* fp);

int fillElementsSum(FILE* fp, Elements* list);
int strToInt(char * str);
int SumToInt(Elements* list, int alpha);