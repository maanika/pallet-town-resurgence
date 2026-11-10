#ifndef _UTIL_
#define _UTIL_

#include <stdlib.h>

int utilGetValidIntInput(const char *prompt, const int min, const int max);

void utilClearScreen(void);

void utilPressEnterToContinue(const char* prompt);

/* arrange the N elements of ARRAY in random order.
 * Only effective if N is much smaller than RAND_MAX;
 * if this may not be the case, use a better random
 * number generator. */
void utilShuffleArray(void *array, size_t n, size_t size);

#endif
