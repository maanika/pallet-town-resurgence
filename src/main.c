#include <stdio.h>
#include <stdint.h>

#include "util.h"

#define WELCOME_MESSAGE                                                                            \
	"Welcome to Pallet town, a quiet village in Kanto... or at least it used to be.\n"         \
	"Reports have surfaced that Team Rocket is operating in the area, hiding among innocent "  \
	"trainers.\nEach night, they strike from the shadows, stealing our Pokemon. By "           \
	"day, they walk among us.\nTrust your instincts and your Pokemon to uncover these Team "   \
	"Rocket grunts.\nThe fate of the village depends on it!"

int main(void)
{

	FILE *file = fopen("./images/town.ans", "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return 1;
	}

	char buffer[4096] = {0};
	size_t bytes_read;

	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
		fwrite(buffer, 1, bytes_read, stdout);
	}

	fclose(file);

	printf("\n%s\n", WELCOME_MESSAGE);

	return 0;
}
