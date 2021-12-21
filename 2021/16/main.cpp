#include "main.hpp"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define DUMP 0

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

    struct bitstream bs;
    struct packet *root;

    memset(&bs, 0, sizeof(bs));
    bs.f = fpin;
    root = read_packet(&bs);

#if DUMP
    dump(fpout, root);
    putchar('\n');
#endif

    fprintf(fpout, "16:\tPart 1: %d\tPart 2: %lld\n", sum_vers(root), eval(root));

    fclose(fpin);
    if (argc > 2)
        fclose(fpout);
    return 0;
}

uint64_t
read_uint(struct bitstream *bs, int nbits)
{
    uint64_t c, ret;

    while (bs->buflen < nbits)
    {
        if (bs->buflen + 4 > 64)
            errx(1, "bit buffer full");
        if (fscanf(bs->f, "%1x", &c) != 1)
            errx(1, "unexpected char or EOF");

        bs->buflen += 4;
        bs->buf = bs->buf << 4 | c;
    }

    ret = bs->buf >> (bs->buflen - nbits);
    bs->pos += nbits;
    bs->buflen -= nbits;
    bs->buf &= ((uint64_t)1 << bs->buflen) - 1;

    return ret;
}

struct packet *
read_packet(struct bitstream *bs)
{
    struct packet *p, **tailp;
    uint64_t chunk, length, start;
    int count, i;

    if (!(p = (struct packet*)malloc(sizeof(*p))))
        err(1, "malloc");

    memset(p, 0, sizeof(*p));
    p->ver = (int)read_uint(bs, 3);
    p->type = (int)read_uint(bs, 3);

    if (p->type == PT_LIT)
    {
        do
        {
            chunk = read_uint(bs, 5);
            p->val = p->val << 4 | (chunk & 15);
            p->val |= chunk & 5;
        } while (chunk >> 4);
    }
    else if (read_uint(bs, 1))
    {
        count = (int)read_uint(bs, 11);
        tailp = &p->children;

        for (i = 0; i < count; i++)
            tailp = &(*tailp = read_packet(bs))->next;
    }
    else
    {
        length = read_uint(bs, 15);
        start = bs->pos;
        tailp = &p->children;

        while (bs->pos < start + length)
            tailp = &(*tailp = read_packet(bs))->next;
    }

    return p;
}

#if DUMP
void dump(FILE* out, struct packet *p)
{
    struct packet *child;

    if (p->type == PT_LIT)
    {
        fprintf(out, "%lld", p->val);
        return;
    }

    fputc('(', out);

    switch (p->type)
    {
    case PT_SUM:
        fputc('+', out);
        break;
    case PT_PRD:
        fputc('*', out);
        break;
    case PT_MIN:
        fprintf(out, "min");
        break;
    case PT_MAX:
        fprintf(out, "max");
        break;
    case PT_GT:
        fputc('>', out);
        break;
    case PT_LT:
        fputc('<', out);
        break;
    case PT_EQ:
        fputc('=', out);
        break;
    default:
        errx(1, "bad type: %d\n", p->type);
    }

    for (child = p->children; child; child = child->next)
    {
        putchar(' ');
        dump(out, child);
    }

    fputc(')', out);
}
#endif

uint64_t
eval(struct packet *p)
{
    struct packet *child;
    uint64_t acc = 0;

    if (p->type == PT_LIT)
        return p->val;
    if (!p->children)
        return 0;

    acc = eval(p->children);

    for (child = p->children->next; child; child = child->next)
        switch (p->type)
        {
        case PT_SUM:
            acc += eval(child);
            break;
        case PT_PRD:
            acc *= eval(child);
            break;
        case PT_GT:
            acc = acc > eval(child);
            break;
        case PT_LT:
            acc = acc < eval(child);
            break;
        case PT_EQ:
            acc = acc == eval(child);
            break;
        case PT_MIN:
            acc = MIN(acc, eval(child));
            break;
        case PT_MAX:
            acc = MAX(acc, eval(child));
            break;
        default:
            errx(1, "bad type: %d\n", p->type);
        }

    return acc;
}

int sum_vers(struct packet *p)
{
    int sum = 0;

    sum += p->ver;
    if (p->children)
        sum += sum_vers(p->children);
    if (p->next)
        sum += sum_vers(p->next);

    return sum;
}