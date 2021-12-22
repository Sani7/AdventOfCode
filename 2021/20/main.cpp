#include "main.hpp"

static char table[513];
static char grid[2][SZ][SZ];
static int gi; /* index of currently active grid */
static int xmin = X0, xmax = X0 - 1, ymin = Y0, ymax = Y0 - 1;

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

    int len, i, p1, p2;

    fscanf(fpin, " %512s", table);
    len = strlen(table);
    for (i = 0; i < len; i++)
        table[i] = table[i] == '#';

    /* account for empty cell rule */
    if (table[0])
        memset(grid[1], 1, sizeof(grid[1]));

    while (fscanf(fpin, " %100s", &grid[0][ymax + 1][X0]) == 1)
    {
        len = (int)strlen(&grid[0][ymax + 1][X0]);
        xmax = MAX(xmax, X0 + len - 1);
        ymax++;
        for (i = 0; i < len; i++)
            grid[0][ymax][X0 + i] = grid[0][ymax][X0 + i] == '#';
        assert(ymax < SZ - 3);
    }

    for (i = 0; i < 2; i++)
    {
        step();
    }
    p1 = count_on();
    for (; i < 50; i++)
    {
        step();
    }
    p2 = count_on();

    fprintf(fpout, "20:\tPart 1: %d\tPart 2: %d\n", p1, p2);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

static void
step(void)
{
    int x, y;

    for (y = ymin - 1; y <= ymax + 1; y++)
        for (x = xmin - 1; x <= xmax + 1; x++)
            grid[!gi][y][x] = table[grid[gi][y - 1][x - 1] << 8 |
                                    grid[gi][y - 1][x] << 7 |
                                    grid[gi][y - 1][x + 1] << 6 |
                                    grid[gi][y][x - 1] << 5 |
                                    grid[gi][y][x] << 4 |
                                    grid[gi][y][x + 1] << 3 |
                                    grid[gi][y + 1][x - 1] << 2 |
                                    grid[gi][y + 1][x] << 1 |
                                    grid[gi][y + 1][x + 1]];

    gi = !gi;
    xmin--;
    xmax++;
    ymin--;
    ymax++;

    assert(xmin > 2);
    assert(xmax < SZ - 3);
    assert(ymin > 2);
    assert(ymax < SZ - 3);
}

static int
count_on(void)
{
    int x, y, n = 0;

    for (y = ymin; y <= ymax; y++)
        for (x = xmin; x <= xmax; x++)
            n += grid[gi][y][x];

    return n;
}