#include "main.hpp"

FILE* fpin, * fpout;

int main(int argc, char** argv)
{
    /* 
     * Use 1 or 2 cmd arguments as file name to use for input and output
     * when argc is 1 then no arguments passed, 2 is one arg and so on
    */
    switch (argc)
    {
    case 1:
        fpin = fopen("test", "r");
        break;
    case 3:
        fpout = fopen(argv[2], "w");
    case 2:
        fpin = fopen(argv[1], "r");
        break;
    default:
        break;
    }

    


    return 0;
}