#include "main.hpp"

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

    struct state st = {};
    int p1;
    struct p2 p2;

    fscanf(fpin, " Player 1 starting position: %d"
                 " Player 2 starting position: %d",
           &st.pos0, &st.pos1);

    st.pos0--; /* 0 indexed */
    st.pos1--;

    p1 = solve_p1(st);
    p2 = solve_p2(st);

    fprintf(fpout, "21:\tPart 1: %d\tPart 2: % " PRIu64 " \n", p1, MAX(p2.wins0, p2.wins1));

    fclose(fpin);
    fclose(fpout);
    return 0;
}

static struct state
apply_throw(struct state st0, int Throw)
{
    struct state st = {};

    st.pos0 = st0.pos1;
    st.pos1 = (st0.pos0 + Throw) % 10;
    st.score0 = st0.score1;
    st.score1 = st0.score0 + st.pos1 + 1;

    return st;
}

static void
add_res(struct p2 *acc, struct p2 res, int count)
{
    acc->wins0 += res.wins1 * count;
    acc->wins1 += res.wins0 * count;
}

static int
solve_p1(struct state st)
{
    int nthrows = 0, Throw, i;

    while (st.score1 < 1000)
    {
        for (Throw = 0, i = 0; i < 3; i++)
            Throw += nthrows++ % 100 + 1;

        st = apply_throw(st, Throw);
    }

    return MIN(st.score0, st.score1) * nthrows;
}

static struct p2
solve_p2(struct state s)
{
    static struct p2 cache[10][21][10][21];
    struct p2 res = {}, *ent;

    ent = &cache[s.pos0][s.score0][s.pos1][s.score1];

    if (s.score1 >= 21)
    {
        res.wins1 = 1;
        return res;
    }
    else if (ent->set)
    {
        return *ent;
    }
    else
    {
        add_res(&res, solve_p2(apply_throw(s, 3)), 1);
        add_res(&res, solve_p2(apply_throw(s, 4)), 3);
        add_res(&res, solve_p2(apply_throw(s, 5)), 6);
        add_res(&res, solve_p2(apply_throw(s, 6)), 7);
        add_res(&res, solve_p2(apply_throw(s, 7)), 6);
        add_res(&res, solve_p2(apply_throw(s, 8)), 3);
        add_res(&res, solve_p2(apply_throw(s, 9)), 1);

        res.set = 1;
        return *ent = res;
    }
}