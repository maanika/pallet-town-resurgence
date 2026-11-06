#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

size_t utilClearScreen(void)
{
	const char *clear_screen_ansi = "\e[1;1H\e[2J";
	return write(STDOUT_FILENO, clear_screen_ansi, sizeof(clear_screen_ansi));
}

int utilGetValidIntInput(const char *prompt, const int min, const int max)
{
	int input = 0;
	int ret = 0;
	do {
		printf("%s", prompt);
		ret = scanf("%d", &input);
	} while (ret != 1 || input < min || input > max);

	return input;
}

#define NELEMS(x) (sizeof(x) / sizeof(x[0]))

void utilShuffleArray(void *array, size_t n, size_t size)
{
	char tmp[size];
	char *arr = array;
	size_t stride = size * sizeof(char);

	if (n > 1) {
		size_t i;
		for (i = 0; i < n - 1; ++i) {
			size_t rnd = (size_t)rand();
			size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

			memcpy(tmp, arr + j * stride, size);
			memcpy(arr + j * stride, arr + i * stride, size);
			memcpy(arr + i * stride, tmp, size);
		}
	}
}
