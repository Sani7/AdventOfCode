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
    
    uint64_t pop[LIFE] = {0};

    int c = ',';
    while (c == ',') {
        pop[fgetc(fpin) - '0']++;
        c = fgetc(fpin);
    }

    fprintf(fpout, "Part 1: %llu\n", live(pop, 0, DAYS1));
    fprintf(fpout, "Part 2: %llu\n", live(pop, DAYS1 % LIFE, DAYS2 - DAYS1));

    //int end = clock();
    //fprintf(fpout, "The code took %d ticks to execute\nAnd equals to %.3f milliseconds\n", end - start, ((float)end - start) / CLOCKS_PER_SEC * 1000);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

uint64_t live(uint64_t* pop, int birth, int days)
{
    for (int i = birth; i < birth + days; ++i)
        pop[(i + CYCLE) % LIFE] += pop[i % LIFE];
    uint64_t census = 0;
    for (int i = 0; i < LIFE; ++i)
        census += pop[i];
    return census;
}