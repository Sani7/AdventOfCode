#include "main.hpp"

char map[102][102];

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

    unsigned long result = 0;
    char buf[105], *bufp;
    int basins[300] = {0};
    int x = 0;

    for (int part = 0; part < 2; part++)
    {
        result = 0;
        fseek(fpin, 0, SEEK_SET);
        memset(map, 9, 102 * 102);
        int j = 1;
        while (fgets(buf, 105, fpin) != NULL)
        {
            bufp = buf;
            if (*bufp == '\n')
                break;
            for (int i = 1; i < 101; i++)
                map[j][i] = *(bufp++) - 48;
            j++;
        }
        for (int i = 1; i < 101; i++)
            for (int j = 1; j < 101; j++)
                if (map[i][j] != 9)
                    if (part == 0)
                    {
                        if ((map[i][j] < map[i - 1][j]) && (map[i][j] < map[i][j - 1]) && (map[i][j] < map[i][j + 1]) && (map[i][j] < map[i + 1][j]))
                            result += map[i][j] + 1;
                    }
                    else
                    {
                        basins[x++] = wall(i, j);
                    }
        if (part == 1)
        {
            qsort(basins, 300, sizeof(int), cmp);
            result = basins[299] * basins[298] * basins[297];
        }
        fprintf(fpout, "Part %d: %lu\t", part + 1, result);
    }
    fprintf(fpout, "\n");
    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

int wall(int i, int j)
{
    int x = 1;
    map[i][j] = 9;
    if (map[i + 1][j] != 9)
        x += wall(i + 1, j);
    if (map[i - 1][j] != 9)
        x += wall(i - 1, j);
    if (map[i][j + 1] != 9)
        x += wall(i, j + 1);
    if (map[i][j - 1] != 9)
        x += wall(i, j - 1);
    return x;
}

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}