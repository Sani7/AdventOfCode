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
        fpin = fopen("test", "r");
        fpout = stdout;
        break;
    case 3:
        fpout = fopen(argv[2], "w");
    case 2:
        fpin = fopen(argv[1], "r");
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
    if (fpout == NULL)
    {
        fprintf(stderr, "Not able to write to file %s\n", argv[2]);
        exit(-2);
    }

    

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