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

    int tx0, tx1, ty0, ty1, vx0, vy0, vx, vy, x, y, p1, p2 = 0;

    fscanf(fpin, "target area: x=%d..%d, y=%d..%d", &tx0, &tx1, &ty0, &ty1);

    p1 = ty0 * (ty0 + 1) / 2;

    for (vx0 = (int)sqrt(tx0) / 2; vx0 <= tx1; vx0++)
        for (vy0 = ty0; vy0 < -ty0; vy0++)
        {
            x = y = 0;
            vx = vx0;
            vy = vy0;
            while ((x < tx0 || y > ty1) && x <= tx1 && y >= ty0)
            {
                x += vx;
                vx -= vx > 0;
                y += vy;
                vy -= 1;
            }
            p2 += x >= tx0 && x <= tx1 && y >= ty0 && y <= ty1;
        }

    fprintf(fpout, "17:\tPart 1: %d\tPart 2: %d\n", p1, p2);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}
