#include "main.hpp"

FILE* fpin, * fpout;

int main(int argc, char** argv)
{
    //int start = clock();
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

    int len = calcFileLength(fpin);
    int *numArray = (int *)malloc(len * sizeof(int));
    
    readFile(fpin, numArray, len);
    
    fprintf(fpout, "Res = %d\n", SumToInt(numArray, len, 1) * SumToInt(numArray, len, 0));

    //int end = clock();
    //fprintf(fpout, "The code took %d ticks to execute\nAnd equals to %.3f milliseconds\n", end - start, ((float)end - start)*1000/CLOCKS_PER_SEC);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

int calcFileLength(FILE* fp)
{
    char buff[BUFSIZ];
    int ret = 0;
    char* tmp;

    fseek(fp, 0, SEEK_SET);
    tmp = fgets(buff, BUFSIZ, fp);
    while(tmp != NULL)
    {
        ret++;
        tmp = fgets(buff, BUFSIZ, fp);
    }
    return ret;
}

void readFile(FILE* in, int* out, int len)
{
    char tmp[BUFSIZ];
    fseek(fpin, 0, SEEK_SET);
    for (int i = 0; i < len; i++)
    {
        fgets(tmp, BUFSIZ, fpin);
        out[i] = strToInt(tmp);
    }
}

int strToInt(char * str)
{
    int i = 0, res = 0;

    while (str[i] != '\0' && str[i] != '\n')
    {
        res = res << 1;
        if (str[i] == '1')
            res++;
        i++; 
    }
    return res;
}

int mostCommonBit(int* num, int len, int bit)
{
    int zero = 0, one = 0;
    for (int i = 0; i < len; i++)
    {
        if (num[i] == -1);
            //fprintf(fpout, "%d is -1\n", i);
        else if ((num[i] >> bit) & 0b1)
            one++;
        else
            zero++;
    }
    fprintf(fpout, "zero: %d, one: %d\n", zero, one);
    if (one == 1 && zero == 0)
        return 0;
    if (zero == 1 && one == 0)
    return 1;
    if (zero < one)
        return 1;
    if (zero == one)
        return 1;
    return 0;
}

int SumToInt(int* list, int len, int alpha)
{
    int res = 0;
    if (alpha)
    {
        for (int i = 0; i < 12; i++)
        {
            res = res << 1;
            if (mostCommonBit(list, len, 11 - i))
            {
                res++;
            }
            fprintf(fpout, "res: %d\n", res);
        }
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            res = res << 1;
            if (!mostCommonBit(list, len, 11 - i))
            {
                res++;
            }
            fprintf(fpout, "res: %d\n", res);
        }
    }
    fprintf(fpout, "%d\n", res);
    return res;
}