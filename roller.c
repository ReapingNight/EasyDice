#include "roller.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int* roll(unsigned int n, unsigned int d, int bonus)
{
    int* res = calloc(n+1, sizeof(int));

    time_t t;
    srand((unsigned) time(&t));

    res[0] = n;

    for (unsigned int ii = 1; ii < n+1; ++ii)
    {
        res[ii] = (rand() % d + 1) + bonus;
    }

    return res;
}