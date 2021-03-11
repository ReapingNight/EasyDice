#include "argsparser.h"
#include "roller.h"
#include "filter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

struct flags
{
    unsigned int d;
    unsigned int n;
    int bonus;
    int flat;
    unsigned int dc;
};

int match(const char *string, const char *pattern)
{
    regex_t re;

    if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) return 0;
    int status = regexec(&re, string, 0, NULL, 0);

    regfree(&re);

    if (status != 0) return 0;
    return 1;
}

void parse_roll(char* dice, Flags * flags)
{

    const char* re = "^[0-9]*(d)?[0-9]+([\\+|-][0-9]+)?$";

    printf("%s match %s: %s\n", dice, re, match(dice, re) ? "true" : "false");

    const char d[2] = "d";
    char* next_token;
    char** tokens = calloc(2, sizeof(char*));

    tokens[0] = strtok(dice, d);
    if (tokens[0] != NULL) tokens[1] = strtok(NULL, d);


    if (tokens[1] != NULL)
    {
        flags->d = atoi(tokens[1]);
        flags->n = atoi(tokens[0]);
    }
    else
    {
        flags->d = atoi(tokens[0]);
        flags->n = 1;
    }

    free(tokens);

    return;
}

void parse_dc(char* dc, Flags * flags)
{
    const char d[2] = "=";
    char* next_token;
    char** tokens = calloc(2, sizeof(char*));

    tokens[0] = strtok(dc, d);
    if (tokens[0] != NULL) tokens[1] = strtok(NULL, d);

    if (tokens[1] != NULL) flags->dc = atoi(tokens[1]);

    free(tokens);

    return;
}

int count(int* rolls)
{
    int res = 0;
    for (int ii = 1; ii < rolls[0]+1; ++ii)
    {
        res += rolls[ii];
    }

    return res;
}

void parse(int argc, char** argv)
{
    int* rolls;

    Flags * flags = (Flags*) malloc(sizeof(*flags));
    flags->d = 0;
    flags->n = 0;
    flags->bonus = 0;
    flags->flat = 0;
    flags->dc = 0;

    parse_roll(argv[1], flags);

    for (int ii = 2; ii < argc; ++ii)
    {
        // if (strcmp(argv[ii], "roll") == 0)          parse_roll(argv[++ii], flags);
        if (argv[ii][0] == '+')                     flags->bonus += atoi(argv[ii]+1);
        else if (argv[ii][0] == '-')                flags->bonus -= atoi(argv[ii]+1);
        else if (strstr(argv[ii], "dc=") != NULL)   parse_dc(argv[ii], flags);
    }

    rolls = roll(flags->n, flags->d, flags->bonus);
    if (flags->dc) rolls = filter(rolls, flags->dc);

    printf("[");

    for (int ii = 1; ii < rolls[0]; ++ii)
    {
        printf("%i, ", rolls[ii]);
    }

    if (flags->dc)
    {
        printf("%i] - %i\n", rolls[rolls[0]], rolls[0]);
    }
    else
    {
        printf("%i] - %i\n", rolls[rolls[0]], count(rolls));
    }

    free(rolls);
    free(flags);

    return;
}