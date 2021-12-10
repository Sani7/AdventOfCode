#include "main.hpp"

#define STACKSIZE 20  // 15 for my input
#define INCSIZE   60  // 54 for my input

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

    int stack[STACKSIZE] = {0};
    int64_t incomplete[INCSIZE] = {0};

    int c, id, score = 0, syntaxerror = 0;
    size_t sp = 0, ip = 0;

        while (!feof(fpin)) {
        switch ((c = fgetc(fpin))) {
            case '(' : id = 0x01; break;
            case '[' : id = 0x02; break;
            case '{' : id = 0x03; break;
            case '<' : id = 0x04; break;
            case ')' : id = 0x10; score = 3; break;
            case ']' : id = 0x20; score = 57; break;
            case '}' : id = 0x30; score = 1197; break;
            case '>' : id = 0x40; score = 25137; break;
            case '\n': id = 0xff; break;
            default  : id = 0x00; break;
        }

        if (id == 0xff) {                             // newline?
            if (sp) {                                 // incomplete?
                if (ip != INCSIZE) {                  // room on the stack?
                    int64_t i = 0;                    // determine incomplete score
                    while (sp)
                        i = i * 5 + stack[--sp];      // pop opening bracket (value 1-4)
                    incomplete[ip++] = i;             // save incomplete score
                } else {
                    fprintf(stderr, "Incomplete-score stack overflow\n Add more to INC Size\n");
                    return 1;
                }
            }
        } else if (id & 0x0f) {                       // opening bracket?
            if (sp != STACKSIZE) {                    // room on the stack?
                stack[sp++] = id;                     // push opening bracket (value 1-4)
            } else {
                fprintf(stderr, "Bracket stack overflow\nAdd more to stack size\n");
                return 2;
            }
        } else if (id & 0xf0) {                       // closing bracket?
            if (!sp || stack[--sp] != id >> 4) {      // empty stack or no match?
                syntaxerror += score;                 // count corruption!!
                while (c != '\n' && !feof(fpin))         // discard rest of line
                    c = fgetc(fpin);
                sp = 0;                               // start a new line
            }
        }
    }
    qsort(incomplete, ip, sizeof *incomplete, asc);

    fprintf(fpout, "Part 1: %d\n", syntaxerror);
    fprintf(fpout, "Part 2: %d\n", incomplete[ip/2]);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

// Sort i64 array in ascending order
int asc(const void *a, const void *b)
{
    const int64_t p = *(const int64_t*)a;
    const int64_t q = *(const int64_t*)b;
    return (q < p) - (p < q);
}