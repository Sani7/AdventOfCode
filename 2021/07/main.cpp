#include "main.hpp"

int main(int argc, char **argv)
{
    //int start = clock();

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
    
    int len = nCount(fpin);
    int* data = (int*)calloc(len, sizeof(int));

    for (int i = 0, a; fscanf(fpin, "%d", &a) == 1; ) {
        data[i++] = a;
        fgetc(fpin);
    }

    // Linear cost => take median
    // N is even, so N/2 is good (N/2-1 will be the same)
    qsort(data, len, sizeof(int), cmp);
    printf("Part 1: %d\n", residualsum(data[len/2], data, len));

    // Quadratic cost => take mean
    // Could go 0 either way because of rounding, but this happens to work for me
    int mean = 1;
    for (int i = 0; i < len; ++i)
        mean += data[i];
    mean /= len;
    printf("Part 2: %d\n", residualexp(mean, data, len));

    //int end = clock();
    //fprintf(fpout, "The code took %d ticks to execute\nAnd equals to %.3f milliseconds\n", end - start, ((float)end - start) / CLOCKS_PER_SEC * 1000);

    free(data);
    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

int nCount(FILE* fp)
{
    int ret, tmp;
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%d%*c", &tmp) > 0)
        ret++;
    fseek(fp, 0, SEEK_SET);
    return ret;
}

int residualsum(int target, int* data, int len)
{
    int rs = 0;
    for (int i = 0; i < len; ++i)
        rs += abs(data[i] - target);
    return rs;
}

int residualexp(int target, int* data, int len)
{
    int rs = 0;
    for (int i = 0; i < len; ++i) {
        int d = abs(data[i] - target), d2 = d >> 1;
        rs += (d & 1) ? d2 * d + d : d2 * d + d2;
        // Or more clear and how the formula from Gauss is known
        // but ever so slightly slower, for some reason:
        // int n = abs(data[i] - target);
        // cost += n * (n + 1) / 2;
    }
    return rs;
}

int cmp(const void *a, const void *b)
{
    int p = *(const int*)a;
    int q = *(const int*)b;
    return (q < p) - (p < q);
}