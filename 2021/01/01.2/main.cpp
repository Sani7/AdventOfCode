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
    int len = calcFileLength(fpin), increase = 0;
    int *numArray = (int *)malloc(len * sizeof(int));
    fseek(fpin, 0, SEEK_SET);
    for (int i = 0; i < len; i++)
    {
        fscanf(fpin, "%d", &numArray[i]);
    }

    for (int i = 0; i < len; i++)
    {
        numArray[i] = numArray[i] + numArray[i + 1] + numArray[i + 2];
    }

    fprintf(fpout, "%d (N/A - no previous measurement)\n", numArray[0]);
    for (int i = 1; i < len; i++)
    {
        if (numArray[i - 1] < numArray[i])
        {
            fprintf(fpout, "%d (increased)\n", numArray[i]);
            increase++;
        }
        else
        {
            fprintf(fpout, "%d (decreased)\n", numArray[i]);
        }
    }

    fprintf(fpout, "Answer: %d\n", increase);

    //int end = clock();
    //fprintf(fpout, "The code took %d ticks to execute\nAnd equals to %.3f milliseconds\n", end - start, ((float)end - start)*1000/CLOCKS_PER_SEC);

    free(numArray);
    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

int calcFileLength(FILE *fp)
{
    char buff[BUFSIZ];
    int ret = 0;
    char *tmp;

    fseek(fp, 0, SEEK_SET);
    tmp = fgets(buff, BUFSIZ, fp);
    while (tmp != NULL)
    {
        ret++;
        tmp = fgets(buff, BUFSIZ, fp);
    }
    return ret;
}