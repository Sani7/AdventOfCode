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

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

/*
 * To halve the required cache size, 'state' does not include a 'current
 * player' field, instead that aspect is encoded in the order - pos0
 * score0 are the current player, pos1 and score1 the other.
 *
 * apply_throw() and add_res() resp. apply and reverse the flip.
 *
 * Credits to /u/4HbQ for the insight.
 */

struct state { int pos0,score0, pos1,score1; };
struct p2 { uint64_t wins0, wins1; char set; };

static struct state
apply_throw(struct state st0, int Throw);
static void
add_res(struct p2 *acc, struct p2 res, int count);
static int
solve_p1(struct state st);
static struct p2
solve_p2(struct state s);