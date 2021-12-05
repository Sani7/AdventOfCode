#include "main.hpp"

int main(int argc, char **argv)
{
    int start = clock();
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

    int y = 0, z = 0, aim = 0;
    char tmp[12];
    int amount, again;

    again = fscanf(fpin, "%s %d", tmp, &amount);
    while (again > 0)
    {
        if (strcmp(tmp, "forward") == 0)
        {
            z += amount;
            y += aim * amount; 
        }
        else if (strcmp(tmp, "down") == 0)
            aim += amount;
        else if (strcmp(tmp, "up") == 0)
            aim -= amount;

        fprintf(fpout, "%7s y=%d,z=%d\n",tmp, y, z);

        again = fscanf(fpin, "%s%d", tmp, &amount);
    }

    fprintf(fpout, "result: y=%d, z=%d, total: %d\n", y, z, y * z);

    int end = clock();
    fprintf(fpout, "The code took %d ticks to execute\nAnd equals to %.3f milliseconds\n", end - start, ((float)end - start)*1000/CLOCKS_PER_SEC);

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