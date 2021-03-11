#include "argsparser.h"
#include "roller.h"
#include "filter.h"
// #include "re.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct flags
{
    unsigned int d;
    unsigned int n;
    int bonus;
    int flat;
    unsigned int dc;
};

void parse_roll(char* dice, Flags * flags)
{
    // // Match valid roll syntax
    // int match;
    // int temp;
    // re_t re_val = re_compile("[0-9]*[d]?[0-9]+[\\+]?[0-9]*");

    // if (temp = re_matchp(re_val, dice, &match) == -1 || match != strlen(dice))
    // {
    //     printf("%i - %i\n", temp, match);
    //     printf("Invalid syntax %s\n", dice);
    // }


    // // Determine whether flat is given
    // re_t re_flat = re_compile("[0-9]*d[0-9]+\\+[0-9]+");

    // if (re_matchp(re_flat, dice, &match) != -1)
    // {
    //     // Split flat from string
    //     printf("Match on flat\n");
    // }
    

    // // Determine whether n is given
    // re_t re_n = re_compile("[0-9]+d[0-9]+");

    // if (re_matchp(re_n, dice, &match) != -1)
    // {
    //     // Split n from string
    //     printf("Match on n\n");
    // }
    

    // // Split whether dice or regular number
    // re_t re_dice = re_compile("d");

    // if (re_matchp(re_dice, dice, &match) != -1)
    // {
    //     // Split d from string
    //     printf("Match dice\n");
    // }

    const char d[2] = "d";
    char* next_token;
    char** tokens = calloc(2, sizeof(char*));

    // tokens[0] = strtok_s(dice, d, &next_token);
    // if (tokens[0] != NULL) tokens[1] = strtok_s(NULL, d, &next_token);

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

    // tokens[0] = strtok_s(dc, d, &next_token);
    // if (tokens[0] != NULL) tokens[1] = strtok_s(NULL, d, &next_token);

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