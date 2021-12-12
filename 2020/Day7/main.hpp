#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>

int getid(const char *name);
void parse(FILE *f);
int holds(int subj, int obj);
int bagCount(int subj);