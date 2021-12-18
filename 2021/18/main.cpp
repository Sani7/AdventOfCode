#include "main.hpp"

struct fish fs[1000];
int nf;

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

    static char ls[101][100];
    int nl = 0, i, j, sc, p1 = 0, p2 = 0;

    while (fgets(ls[nl], sizeof(ls[nl]), fpin))
    {
        add_str(ls[nl]);
        if (++nl >= LEN(ls))
            errx(1, "lines overflow");
    }

    p1 = score();

    for (i = 0; i < nl; i++)
        for (j = 0; j < nl; j++)
        {
            if (i == j)
                continue;
            nf = 0;
            add_str(ls[i]);
            add_str(ls[j]);
            if ((sc = score()) > p2)
                p2 = sc;
        }

    fprintf(fpout, "Part 1: %d\nPart 2: %d\n", p1, p2);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

static int
explode(void)
{
    int i;

    for (i = 1; i < nf; i++)
        if (fs[i - 1].d == 5 && fs[i].d == 5)
        {
            if (i > 1)
                fs[i - 2].n += fs[i - 1].n;
            if (i + 1 < nf)
                fs[i + 1].n += fs[i].n;
            fs[i - 1].n = 0;
            fs[i - 1].d--;
            nf--;
            memmove(fs + i, fs + i + 1, (nf - i) * sizeof(*fs));
            return 1;
        }

    return 0;
}

static int
split(void)
{
    int i;

    for (i = 0; i < nf; i++)
        if (fs[i].n > 9)
        {
            if (++nf > LEN(fs))
                errx(1, "overflow");
            memmove(fs + i + 1, fs + i, (nf - i - 1) * sizeof(*fs));
            fs[i].d = ++fs[i + 1].d;
            fs[i].n = fs[i + 1].n / 2;
            fs[i + 1].n = fs[i + 1].n - fs[i].n;
            return 1;
        }

    return 0;
}

static int
score(void)
{
    int i, any = 1;

    while (nf > 1 && any)
        for (i = 0, any = 0; i < nf - 1; i++)
        {
            if (fs[i].d != fs[i + 1].d)
                continue;
            fs[i].n = 3 * fs[i].n + 2 * fs[i + 1].n;
            fs[i].d--;
            nf--;
            any = 1;
            memmove(fs + i + 1, fs + i + 2, (nf - i - 1) * sizeof(*fs));
        }

    return nf == 1 ? fs[0].n : 0;
}

static void
add_str(const char *s)
{
    int i, d;

    for (i = 0; i < nf; i++)
        fs[i].d++;
    for (i = 0, d = nf > 1; s[i]; i++)
        if (s[i] == '[')
            d++;
        else if (s[i] == ']')
            d--;
        else if (s[i] >= '0' && s[i] <= '9')
        {
            fs[nf].n = s[i] - '0';
            fs[nf].d = d;
            if (++nf >= LEN(fs))
                errx(1, "overflow");
        }
    while (explode() || split())
        ;
}