#include <stdio.h>
#include <stdint.h>

#include "util.h"
#include "game.h"

#define WELCOME_MESSAGE                                                                            \
	"\nWelcome to Pallet town, a quiet village in Kanto... or at least it used to be.\n"       \
	"Reports have surfaced that Team Rocket is operating in the area, hiding among innocent "  \
	"trainers.\nEach night, they strike from the shadows, stealing our Pokemon. By "           \
	"day, they walk among us.\nTrust your instincts and your Pokemon to uncover these Team "   \
	"Rocket grunts.\nThe fate of the village depends on it!\n\n"

int main(void)
{
	utilClearScreen();

	FILE *file = fopen("./images/town.ans", "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return 1;
	}

	char buffer[4096] = {0};
	size_t bytes_read = 0;
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
		fwrite(buffer, 1, bytes_read, stdout);
	}

	fclose(file);

	printf("\n%s\n", WELCOME_MESSAGE);

	const int num_of_players = utilGetValidIntInput(
		"Enter number of players (between 4 and 10 players)?\n", 4, 10);
	(void)num_of_players;

	Game *game = gameCreate(num_of_players);
	gameStart(game);
	gameEnd(game);

	return 0;
}

// ** Notes **
//
// Game Rules:
//  - Trainer
//      Night:
//          No special ability at Night.
//      Day:
//          Can vote who to battle during the day.
//
//  - Gym Leader
//      Night:
//          Can battle if targeted at Night.
//          Wins the battle if move selcted by Team Rocket is less effective.
//          Team Rocket gets away without any pokemon stolen if they loose.
//      Day:
//          Can vote who to battle during the day.
//
//  - Officer Jenny
//      Night:
//          Can select who to protect during the Night.
//      Day:
//          Can vote who to battle during the day
//
//  - Team Rocket
//      Night:
//          Selects which trainer to steal their Pokemon
//      Day:
//          Does nothing. No right to vote. Hide!
