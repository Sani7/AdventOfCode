#include "main.hpp"

int main(int argc, char** argv)
{
    FILE* fpin, * fpout;
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

    Line line[LINES] = {0};
    int vent[DIM][DIM] = {0};

    int i = 0, x0, y0, x1, y1, dx, dy;
    while (i < LINES && fscanf(fpin, "%d,%d -> %d,%d ", &x0, &y0, &x1, &y1) == 4) {
        dx = x0 < x1 ? 1 : (x0 > x1 ? -1 : 0);
        dy = y0 < y1 ? 1 : (y0 > y1 ? -1 : 0);
        line[i++] = (Line){x0, y0, x1, y1, dx, dy, dx && dy};
    }
    if (i != LINES)
        return 2;

    fprintf(fpout, "Part 1: %d\n", multivent(false, line, vent));
    fprintf(fpout, "Part 2: %d\n", multivent(true, line, vent));

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}


int multivent(bool diag, Line* line, int vent[][DIM])
{
    for (int i = 0; i < LINES; ++i) {
        if (diag == line[i].diag) {
            int x = line[i].x0;
            int y = line[i].y0;
            while (x != line[i].x1 || y != line[i].y1) {
                vent[x][y]++;
                x += line[i].dx;
                y += line[i].dy;
            }
            vent[x][y]++;
        }
    }

    int multiple = 0;
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            multiple += vent[i][j] > 1;
    return multiple;
}