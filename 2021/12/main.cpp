#include "main.hpp"

int edges[maxSize][maxSize];
int edgesLen[maxSize] = {0};

char nameToID[maxSize][maxSize];
int nameToIDLen = 0;

bool isLarge[maxSize] = {false};
bool isVisited[maxSize] = {false};

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

    // Register starting node as 0 and ending node as 1. Start and end are small.
    strcpy(nameToID[0], "start");
    strcpy(nameToID[1], "end");
    nameToIDLen = 2;
    // Get input
    char str[maxSize];
    char *from, *to;
    while (!feof(fpin))
    {
        fscanf(fpin, "%s", str);
        from = str;
        // Find -, replace with null byte. Make from and to point to the strings.
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == '-')
            {
                str[i] = '\0';
                to = &str[i + 1];
            }
        }
        // convert names to ID, why do you make the input so hard AOC? I'm just a poor C programmer.
        int fromID = getID(from);
        int toID = getID(to);
        if (fromID == -1)
            fromID = makeID(from);
        if (toID == -1)
            toID = makeID(to);
        // make adjacency list
        edges[fromID][edgesLen[fromID]++] = toID;
        edges[toID][edgesLen[toID]++] = fromID;
    }

    // DFS from start, every time an end is hit, +1 to path count. Backtrack properly.
    int pathCnt = 0;
    dfs(START_NODE, &pathCnt);
    printf("12:\tPart 1: %d\t", pathCnt);

    pathCnt = 0;
    int wildcard = -1;
    dfs2(START_NODE, &pathCnt, &wildcard);
    printf("Part 2: %d\n", pathCnt);

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

// Given a string, return the ID if it has already been seen. Else return -1 if it is a new string.
// Sorry you're gonna have to live with O(n) because I'm not making a hashmap in C.
int getID(char *str)
{
    for (int i = 0; i < nameToIDLen; ++i)
    {
        if (strcmp(str, nameToID[i]) == 0)
            return i;
    }
    return -1;
}

// Given a string, register it into the nameToID array and return its ID.
int makeID(char *str)
{
    strcpy(nameToID[nameToIDLen], str);
    if (isupper(str[0]))
        isLarge[nameToIDLen] = true;
    return nameToIDLen++;
}

// Part 1
void dfs(int from, int *pathCntPtr)
{
    if (!isLarge[from])
        isVisited[from] = true;

    for (int i = 0; i < edgesLen[from]; ++i)
    {
        int to = edges[from][i];
        if (to == END_NODE)
            ++(*pathCntPtr);
        else if (!isVisited[to])
            dfs(to, pathCntPtr);
    }

    if (!isLarge[from])
        isVisited[from] = false;
}

// Part 2
// If no small caves were visited, -1. If a small cave is visited, put its ID.
void dfs2(int from, int *pathCntPtr, int* wildcard)
{
    if (from == START_NODE || from == END_NODE)
        isVisited[from] = true;
    else if (!isLarge[from] && !isVisited[from])
        isVisited[from] = true;
    else if (!isLarge[from] && *wildcard == -1)
        *wildcard = from;

    for (int i = 0; i < edgesLen[from]; ++i)
    {
        int to = edges[from][i];
        if (to == END_NODE)
        {
            ++(*pathCntPtr);
        }
        else if (!isVisited[to] || (to != START_NODE && to != END_NODE && *wildcard == -1))
            dfs2(to, pathCntPtr, wildcard);
    }

    if (from == START_NODE || from == END_NODE)
        isVisited[from] = false;
    else if (!isLarge[from] && *wildcard == from)
        *wildcard = -1;
    else if (!isLarge[from])
        isVisited[from] = false;
}