#include "main.hpp"

#define SQUARE 100

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

    run(fpin, fpout, 0);
    run(fpin, fpout, 1);
    

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

void run(FILE* in, FILE* out, unsigned char part)
{
    char buf[105], *bufp;
    int spots[SQUARE * 5][SQUARE * 5][2];
    int x = 0, y, flag = 1, end, tile;

    fseek(in, 0, SEEK_SET);
    memset(spots, 10, 50 * SQUARE * SQUARE * sizeof(int));
    while (fgets(buf, 105, in) != NULL)
    {
        bufp = buf;
        for (int i = 0; *bufp != '\n'; i++)
            spots[x][i][0] = (*(bufp++)) - 48;
        x++;
    }
    end = (part == 0 ? SQUARE - 1 : SQUARE * 5 - 1);
    if (part == 1)
        for (x = 0; x <= end; x++)
            for (y = 0; y <= end; y++)
            {
                tile = x / SQUARE + y / SQUARE;
                spots[x][y][0] = spots[x % SQUARE][y % SQUARE][0] + tile;
                if (spots[x][y][0] > 9)
                    spots[x][y][0] -= 9;
            }
    spots[end][end][1] = spots[end][end][0];
    while (flag)
    {
        flag = 0;
        for (x = end; x >= 0; x--)
            for (y = end; y >= 0; y--)
            {
                if ((x < end) && (spots[x + 1][y][1] + spots[x][y][0] < spots[x][y][1]))
                {
                    flag = 1;
                    spots[x][y][1] = spots[x + 1][y][1] + spots[x][y][0];
                }
                if ((x) && (spots[x - 1][y][1] + spots[x][y][0] < spots[x][y][1]))
                {
                    flag = 1;
                    spots[x][y][1] = spots[x - 1][y][1] + spots[x][y][0];
                }
                if ((y < end) && (spots[x][y + 1][1] + spots[x][y][0] < spots[x][y][1]))
                {
                    flag = 1;
                    spots[x][y][1] = spots[x][y + 1][1] + spots[x][y][0];
                }
                if ((y) && (spots[x][y - 1][1] + spots[x][y][0] < spots[x][y][1]))
                {
                    flag = 1;
                    spots[x][y][1] = spots[x][y - 1][1] + spots[x][y][0];
                }
            }
    }
    fprintf(out, "Part %d: %ld\n", part + 1, spots[0][0][1] - spots[0][0][0]);
}