#include "main.hpp"

    FILE* fpin, * fpout;

int main(int argc, char** argv)
{

    Elements sum;
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

    fillElementsSum(fpin, &sum);
    
    fprintf(fpout, "Res = %d", SumToInt(&sum, 1) * SumToInt(&sum, 0));

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

int fillElementsSum(FILE* fp, Elements* list)
{
    char buff[BUFSIZ];
    char * again;
    int len;
    fseek(fp, 0, SEEK_SET);

    again = fgets(buff, BUFSIZ, fp);
    while (again != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            if (buff[i] == '0')
                list->E[i].zeros++;
            else
                list->E[i].ones++;
            fprintf(fpout, "i: %d 1:%d 0:%d\n", i, list->E[i].ones, list->E[i].zeros);
        }
        again = fgets(buff, BUFSIZ, fp);
    }
    return 0;
}

int strToInt(char * str)
{
    int i = 0, res = 0;

    while (str[i] != '\0')
    {
        res = res << 1;
        if (str[i] == '1')
            res++;
        i++; 
    }
    return res;
}

int SumToInt(Elements* list, int alpha)
{
    int res = 0;
    if (alpha)
    {
        for (int i = 0; i < 12; i++)
        {
            res = res << 1;
            if (list->E[i].ones > list->E[i].zeros)
            {
                res++;
            }
            fprintf(fpout, "ones: %d, zeros: %dres: %d\n",list->E[i].ones, list->E[i].zeros, res);
        }
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            res = res << 1;
            if (list->E[i].ones < list->E[i].zeros)
            {
                res++;
            }
            fprintf(fpout, "res: %d\n", res);
        }
    }
    fprintf(fpout, "%d\n", res);
    return res;
}