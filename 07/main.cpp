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

    int target = 0;
    for (int i = 0; i < len; ++i)
        target += data[i];
    target = (target + len/2) / len;

    int dir = 1;
    int res = residualsum(target, data, len), next = residualsum(target + dir, data, len);
    if (next >= res) {
        dir *= -1;
        next = residualsum(target + dir, data, len);
    }
    while (next < res) {
        target += dir;
        res = next;
        next = residualsum(target + dir, data, len);
    }
    printf("Part 1: %d\n", res);

    dir = 1;
    res = residualexp(target, data, len);
    next = residualexp(target + dir, data, len);
    if (next >= res) {
        dir *= -1;
        next = residualexp(target + dir, data, len);
    }
    while (next < res) {
        target += dir;
        res = next;
        next = residualexp(target + dir, data, len);
    }
    printf("Part 2: %d\n", res);

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
    }
    return rs;
}