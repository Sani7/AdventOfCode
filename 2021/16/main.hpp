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

struct packet
{
    int ver;
    int type;
#define PT_SUM 0
#define PT_PRD 1
#define PT_MIN 2
#define PT_MAX 3
#define PT_LIT 4
#define PT_GT 5
#define PT_LT 6
#define PT_EQ 7
    uint64_t val;
    struct packet *children;
    struct packet *next;
};

struct bitstream
{
    FILE *f;
    uint64_t pos;
    uint64_t buf;
    int buflen;
};

uint64_t
read_uint(struct bitstream *bs, int nbits);
struct packet *
read_packet(struct bitstream *bs);
void dump(FILE* out, struct packet *p);
uint64_t
eval(struct packet *p);
int sum_vers(struct packet *p);