#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEAM_ROCKET_GRUNTS 1

typedef enum {
	DAY,
	NIGHT,
} TimeOfDay;

typedef struct {
	int num_players;
	int num_team_rocket_grunts_left;
	int num_trainers_left;
	TimeOfDay time_of_day;
	int num_pokemon_stolen_this_round;
	int num_pokemon_saved_this_round;
	int pokemon_stolen_trainer_ids[TEAM_ROCKET_GRUNTS];
} Game;

static void gameInitRound(Game *game)
{
    assert(game != NULL);
	game->num_pokemon_saved_this_round = 0;
	game->num_pokemon_stolen_this_round = 0;
	memset(game->pokemon_stolen_trainer_ids, -1, sizeof(game->pokemon_stolen_trainer_ids));
	return;
}

Game *gameCreate(int num_players)
{
	Game *game = malloc(sizeof(Game));
	if (!game) {
		exit(EXIT_FAILURE);
	}
	game->num_players = num_players;
	game->num_team_rocket_grunts_left = TEAM_ROCKET_GRUNTS;
	game->num_trainers_left = num_players - TEAM_ROCKET_GRUNTS;
	game->time_of_day = NIGHT;
	gameInitRound(game);

	printf("Game created with %d players\n", num_players);
	return game;
}

void gameStart(Game *game)
{
    assert(game != NULL);

	while (1) {
		printf("Game Start!\n");
		break;
	}

	return;
}

void gameEnd(Game *game)
{
    assert(game != NULL);
	free(game);
	printf("Game End\n");
}
