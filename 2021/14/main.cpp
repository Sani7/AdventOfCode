#include "main.hpp"

#define LINE_LENGTH 100

#define val(a_letter) ((a_letter) - 'A')
#define chr(an_int) ((an_int) + 'A')
#define pair(left_int, right_int) (26 * (left_int) + (right_int))
#define left(pair_number) ((pair_number) / 26)
#define right(pair_number) ((pair_number) % 26)

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
    fprintf(fpout, "14:\t");
    run(fpin, fpout, 10, 1);
    run(fpin, fpout, 40, 2);
    fprintf(fpout, "\n");

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

void count_template(const char* input, long* nb_pairs)
{
    for (int i = 0; i < 26*26; i++) {
        nb_pairs[i] = 0L;
    }
    for (int i = 0; isupper(input[i+1]); i++) {
        int pair = pair(val(input[i]), val(input[i+1]));
		nb_pairs[pair] += 1;
    }
}

void execute_step(long* nb_pairs, const int* insertions)
{
    long tmp [26*26] = {0};
    for (int p = 0; p < 26*26; p++) {
        if (insertions[p] >= 0) {
            tmp[pair(left(p), insertions[p])] += nb_pairs[p];
            tmp[pair(insertions[p], right(p))] += nb_pairs[p];
        }
    }
    for (int i = 0; i < 26*26; i++) {
        nb_pairs[i] = tmp[i];
    }
}

void run(FILE* datafile, FILE* output, int nb_steps, int partNum)
{
    long nb_pairs[26 * 26]; // pairs in template
    char line[LINE_LENGTH];

    fseek(datafile, 0, SEEK_SET);
    fgets(line, LINE_LENGTH, datafile);
    count_template(line, nb_pairs);
    int first = val(line[0]);

    // forget empty line
    fgets(line, LINE_LENGTH, datafile);

    // read rules
    int insertions[26*26];
    for (int i = 0; i < 26*26; i++) insertions[i] = -1;

    while (fgets(line, LINE_LENGTH, datafile) != NULL) {
        char left, right, middle;
        sscanf(line, "%c%c -> %c", &left, &right, &middle);
        int pair = pair(val(left), val(right));
        insertions[pair] = val(middle);
    }
  
    // apply steps 
    for (int k = 0; k < nb_steps; k++) {
        execute_step(nb_pairs,  insertions)	;
    }
    // compute stats
    long count[26] = {0};
    count[first] = 1L;
    for (int p = 0; p < 26*26; p++) {
        count[right(p)] += nb_pairs[p];
    }
  
    long min = LONG_MAX, max = LONG_MIN;;
    for (int i = 0; i < 26; i ++) {
        if (count[i] > 0) {
            if (count[i] < min) min = count[i] ;
            if (count[i] > max) max = count[i] ;
        }
    }

    // print res
   fprintf(output, "Part %d: %ld\t", partNum, max-min);

}