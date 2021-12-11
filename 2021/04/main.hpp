#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "../libs/quickSort/quickSort.hpp"

#define DRAW 100  // how many numbers drawn, range 0..DRAW-1
#define CARD 100  // number of cards in the game
#define DIM    5  // number of rows and columns on every card

typedef struct Index {
    struct Index *next;
    unsigned char card, row, col;
} Index;

