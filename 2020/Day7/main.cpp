#include "main.hpp"

#define LEN(a) ((int)(sizeof(a)/sizeof(*(a))))

char names[1024][32];
int counts[1024][1024];
int nNames;

int main(int argc, char **argv) {
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
    int i, p1 = 0, p2, gold;

    assert(fpin);

    parse(fpin);
    gold = getid("shiny gold");
    for (i = 0; i < nNames; i++)
        p1 += holds(i, gold);
    p2 = bagCount(gold) - 1;

    fprintf(fpout, "Part 1: %d\nPart 2: %d\n", p1, p2);
    //getchar();

        fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

int getid(const char *name) {
    int i;

    for (i = 0; i < nNames; i++)
        if (!strcmp(names[i], name))
            return i;

    nNames++;
    assert(nNames <= LEN(names));
    snprintf(names[i], LEN(names[i]), "%s", name);

    return i;
}

void parse(FILE *f) {
    char adj[16], col[16], name[32];
    int c = 0, subj, count;

    while (c != EOF) {
        if (fscanf(f, "%15s %15s", adj, col) != 2)
            return;
        snprintf(name, 32, "%s %s", adj, col);
        subj = getid(name);

        while ((c = fgetc(f)) != EOF && c != '\n')
            if (isdigit(c)) {
                ungetc(c, f);
                break;
            }
        while (c != EOF && c != '\n') {
            if (fscanf(f, " %d %15s %15s", &count, adj, col)
                != 3)
                return;
            snprintf(name, 32, "%s %s", adj, col);
            counts[subj][getid(name)] = count;

            while ((c = fgetc(f)) != EOF && c != ',' && c != '\n');
        }
    }
}

int holds(int subj, int obj) {
    int i;

    if (counts[subj][obj])
        return 1;
    for (i = 0; i < nNames; i++)
        if (counts[subj][i] && holds(i, obj))
            return 1;
    return 0;
}

int bagCount(int subj) {
    int i, acc = 1;

    for (i = 0; i < nNames; i++)
        if (counts[subj][i])
            acc += counts[subj][i] * bagCount(i);
    return acc;
}