#include "main.hpp"

int main(int argc, char **argv)
{

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

    int lum[DIM + 2][DIM + 2] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 4, 8, 3, 1, 4, 3, 2, 2, 3, 0},
        {0, 2, 7, 4, 5, 8, 5, 4, 7, 1, 1, 0},
        {0, 5, 2, 6, 4, 5, 5, 6, 1, 7, 3, 0},
        {0, 6, 1, 4, 1, 3, 3, 6, 1, 4, 6, 0},
        {0, 6, 3, 5, 7, 3, 8, 5, 4, 7, 8, 0},
        {0, 4, 1, 6, 7, 5, 2, 4, 6, 4, 5, 0},
        {0, 2, 1, 7, 6, 8, 4, 1, 7, 2, 1, 0},
        {0, 6, 8, 8, 2, 8, 8, 1, 1, 3, 4, 0},
        {0, 4, 8, 4, 6, 8, 4, 8, 5, 5, 4, 0},
        {0, 5, 2, 8, 3, 7, 5, 1, 5, 2, 6, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    bool flashed[DIM + 2][DIM + 2] = {0};

    for (int i = 1; i <= DIM; ++i)
    {
        for (int j = 1; j <= DIM; ++j)
            lum[i][j] = (unsigned char)(fgetc(fpin) - '0');
        fgetc(fpin); // newline
    }

    int step = 0, total = 0;
    while (step < STEPS)
    {
        step++;
        total += cascade(lum, flashed);
    }
    fprintf(fpout, "Part 1: %d\n", total);
    while (!all(flashed))
    {
        step++;
        cascade(lum, flashed);
    }
    fprintf(fpout, "Part 2: %d\n", step);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

int cascade(int lum[DIM + 2][DIM + 2], bool flashed[DIM + 2][DIM + 2])
{
    for (int i = 1; i <= DIM; ++i)
        for (int j = 1; j <= DIM; ++j)
        {
            lum[i][j]++;
            flashed[i][j] = false;
        }
    bool check = true;
    while (check)
    {
        check = false;
        for (int i = 1; i <= DIM; ++i)
            for (int j = 1; j <= DIM; ++j)
                if (lum[i][j] >= FLASH && !flashed[i][j])
                {
                    check = true;
                    flashed[i][j] = true;
                    for (int x = i - 1; x <= i + 1; ++x)
                        for (int y = j - 1; y <= j + 1; ++y)
                            lum[x][y]++;
                }
    }
    int n = 0;
    for (int i = 1; i <= DIM; ++i)
        for (int j = 1; j <= DIM; ++j)
            if (lum[i][j] >= FLASH)
            {
                lum[i][j] = 0;
                ++n;
            }
    return n;
}

bool all(bool flashed[DIM + 2][DIM + 2])
{
    for (int i = 1; i <= DIM; ++i)
        for (int j = 1; j <= DIM; ++j)
            if (!flashed[i][j])
                return false;
    return true;
}