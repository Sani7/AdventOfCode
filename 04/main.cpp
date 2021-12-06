#include "main.hpp"

int main(int argc, char **argv)
{
    //int start = clock();
    FILE *fpin, *fpout;
    /* 
     * Use 1 or 2 cmd arguments as file name to use for input and output
     * when argc is 1 then no arguments passed, 2 is one arg and so on
    */
    switch (argc)
    {
    case 1:
        fpin = fopen("input", "r");
        fpout = stdout;
        break;
    case 3:
        fpout = fopen(argv[2], "w");
        if (fpout == NULL)
        {
            fprintf(stderr, "Not able to write to file %s\n", argv[2]);
            exit(-2);
        }
        fpin = fopen(argv[1], "r");
        break;
    case 2:
        fpin = fopen(argv[1], "r");
        fpout = stdout;
        break;
    default:
        break;
    }
    if (fpin == NULL && argc > 1)
    {
        fprintf(stderr, "Not able to acces input file %s\n", argv[1]);
        exit(-1);
    }
    else if (fpin == NULL)
    {
        fprintf(stderr, "Not able to acces input file test\n");
        exit(-1);
    }
    unsigned char draw[DRAW] = {0};           // numbers drawn
    unsigned char card[CARD][DIM][DIM] = {0}; // bingo cards
    unsigned char crossrow[CARD][DIM] = {0};  // count crosses in rows
    unsigned char crosscol[CARD][DIM] = {0};  // count crosses in cols

    Index *index[DRAW] = {0};

    unsigned int i = 0;
    unsigned char a;
    // Get numbers drawn
    if (fscanf(fpin, "%hhu", &a) == 1)
        draw[i++] = a;  // first number drawn
    while (i < DRAW && fscanf(fpin, ",%hhu", &a) == 1)
        draw[i++] = a;  // 99 more numbers drawn with a comma separator
    
    // Get Cards
    unsigned char b = 0, r = 0, c = 0;
    Index *p, *q;
    while (b < CARD && fscanf(fpin, " %hhu", &a) == 1) {
        // Fill the cards
        card[b][r][c] = a;

        // Enter a reference in the reverse index
        p = (Index*)malloc(sizeof(Index));
        *p = (Index){NULL, b, r, c};
        if ((q = index[a])) {  // already an entry for this number?
            while (q->next)
                q = q->next;
            q->next = p;  // add to end of list (order not important)
        } else {
            index[a] = p;  // first entry into the array of linked list base pointers
        }

        // Next position on the card, or next card
        if (++c == DIM) {
            c = 0;
            if (++r == DIM) {
                r = 0;
                ++b;
            }
        }
    }

    unsigned char wins = 0;   // total number of cards that won
    bool won[CARD] = {false};
    for (i = 0; i < DRAW; ++i) {
        p = index[draw[i]];  // first entry in reverse index of number drawn
        while (p) {          // as long as there are entries
            // Only process cards that have not yet won
            if (!won[p->card]) {
                // Cross out = set number on card to 100 (bigger than any number used)
                card[p->card][p->row][p->col] = DRAW;
                crossrow[p->card][p->row]++;  // can't do this in the "if" because of short-circuit evaluation
                crosscol[p->card][p->col]++;
                // Full row or column?
                if (crossrow[p->card][p->row] == DIM || crosscol[p->card][p->col] == DIM) {
                    ++wins;
                    won[p->card] = true;
                    // Calculate score for first and last wins
                    if (wins == 1 || wins == DRAW) {
                        unsigned int cardsum = 0;
                        for (unsigned int j = 0; j < DIM; ++j)
                            for (unsigned int k = 0; k < DIM; ++k)
                                if (card[p->card][j][k] < DRAW)  // not crossed out?
                                    cardsum += card[p->card][j][k];
                        fprintf(fpout, "Part %d: %u\n", 1 + (wins == DRAW), draw[i] * cardsum);
                    }
                }
            }
            p = p->next;  // next entry in reverse index of number drawn
        }
    }

    // Free allocated memory
    for (i = 0; i < DRAW; ++i) {
        p = index[i];
        while (p) {
            q = p->next;
            free(p);
            p = q;
        }
    }
    
    //int end = clock();
    //fprintf(fpout, "The code took %d ticks to execute\nAnd equals to %.3f milliseconds\n", end - start, ((float)end - start)*1000/CLOCKS_PER_SEC);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}