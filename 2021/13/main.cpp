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

    int result = 0;
    int part = 0;
    char buf[18], *bufp;
    char dots[1500][1500] = {0};
    int x, y, maxx = 0, maxy = 0, dir, crease;

    fseek(fpin, 0, SEEK_SET);

    while (fgets(buf, 18, fpin) != NULL)
    {
        bufp = buf;
        if (*bufp == '\n')
            break;
        x = strtol(bufp, &bufp, 10);
        y = strtol(bufp + 1, &bufp, 10);
        dots[y][x] = 1;
        if (x > maxx)
            maxx = x;
        if (y > maxy)
            maxy = y;
    }
    maxx++;
    maxy++;
    while (fgets(buf, 18, fpin) != NULL)
    {
        bufp = strtok(buf, " ");
        bufp = strtok(NULL, " ");
        bufp = strtok(NULL, "=");
        if (*bufp == 'x')
            dir = 1;
        if (*bufp == 'y')
            dir = 0;
        bufp = strtok(NULL, " ");
        crease = strtol(bufp, NULL, 10);
        for (int i = 0; (crease + i) < (dir == 0 ? maxy : maxx); i++)
            for (int j = 0; j < (dir == 1 ? maxy : maxx); j++)
                if (dots[dir ? j : (crease + i)][dir ? (crease + i) : j])
                    dots[dir ? j : (crease - i)][dir ? (crease - i) : j] = 1;
        if (dir)
            maxx = crease;
        else
            maxy = crease;
        if (part == 0)
        {
            for (x = 0; x < maxx; x++)
                for (y = 0; y < maxy; y++)
                    if (dots[y][x])
                        result++;
            part++;
        }
    }
    fprintf(fpout, "Part 1: %d\n", result);
    for (y = 0; y < maxy; y++)
    {
        for (x = 0; x < maxx; x++)
            if (dots[y][x])
                fprintf(fpout, "*");
            else
                fprintf(fpout, " ");
        fprintf(fpout, "\n");
    }

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}
