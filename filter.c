#include "filter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* filter(int* rolls, int dc)
{
    int num_passes = 0;
    for (int ii = 1; ii < rolls[0]+1; ++ii)
    {
        if (rolls[ii] >= dc) num_passes++;
    }

    int* new_rolls = (int*) calloc(num_passes+1, sizeof(int));

    new_rolls[0] = num_passes;

    size_t jj = 1;
    for (int ii = 1; ii < rolls[0]+1; ++ii)
    {
        if (rolls[ii] >= dc) new_rolls[jj++] = rolls[ii];
    }
    free(rolls);
    return new_rolls;
}
