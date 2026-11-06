#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "game.h"
#include "util.h"

#define TEAM_ROCKET_GRUNTS 1

typedef enum {
	DAY,
	NIGHT,
} TimeOfDay;

struct Game {
	int num_players;
	int num_team_rocket_left;
	int num_trainers_left;
	TimeOfDay time_of_day;
	int num_pokemon_stolen_this_round;
	int num_pokemon_saved_this_round;
	int pokemon_stolen_trainer_ids[TEAM_ROCKET_GRUNTS];
	Player **players;
};

static void gameInitRound(Game *game)
{
	assert(game != NULL);
	game->num_pokemon_saved_this_round = 0;
	game->num_pokemon_stolen_this_round = 0;
	memset(game->pokemon_stolen_trainer_ids, -1, sizeof(game->pokemon_stolen_trainer_ids));
	return;
}

static void gameInitPlayers(Player **players, const int num_players)
{
	// Initialse all roles as trainers
	Role *roles = malloc(sizeof(Role) * num_players);
	for (int i = 0; i < num_players; i++) {
		*(roles + i) = TRAINER;
	}

	// Assign special roles
	Role special_roles[3] = {TEAM_ROCKET_GRUNT, OFFICER_JENNY, GYM_LEADER};
	memcpy(roles, special_roles, sizeof(special_roles));

	// Shuffle roles
	utilShuffleArray(roles, num_players, sizeof(Role));

	for (int i = 0; i < num_players; i++) {
		players[i] = playerCreate(i, roles[i]);
	}

	for (int i = 0; i < num_players; i++) {
		printf("Player id %d, Role %s\n", players[i]->player_id,
		       playerRoleToString(players[i]->role));
	}

	free(roles);
}

static Player **gameCreatePlayers(const int num_players)
{
	// Allocate memory for the array of pointers (Player*)
	Player **players = malloc(sizeof(Player *) * num_players);
	if (!players) {
		exit(EXIT_FAILURE);
	}

	gameInitPlayers(players, num_players);

	return players;
}

static void gameDestroyPlayers(Game *game)
{
	for (int i = 0; i < game->num_players; i++) {
		playerDeinit(game->players[i]);
	}
	free(game->players);
}

typedef enum {
	GAME_WINNER_NONE,
	GAME_WINNER_TEAM_ROCKET,
	GAME_WINNER_TOWN_SAVED,
} GameWinner;

static GameWinner gameGetWinner(Game *game)
{
	if (game->num_team_rocket_left >= game->num_trainers_left) {
		return GAME_WINNER_TEAM_ROCKET;
	} else if (game->num_team_rocket_left == 0) {
		return GAME_WINNER_TOWN_SAVED;
	}
	return GAME_WINNER_NONE;
}

void gameStart(Game *game)
{
	assert(game != NULL);

	while (gameGetWinner(game) == GAME_WINNER_NONE) {
		break;
	}

	printf("\n\n%s\n\n", gameGetWinner(game) == GAME_WINNER_TOWN_SAVED
				     ? "Pallet Town is Saved :) !!!!"
				     : "Team Rocket Wins :( ....");

	return;
}

Game *gameCreate(int num_players)
{
	Game *game = malloc(sizeof(Game));
	if (!game) {
		exit(EXIT_FAILURE);
	}
	game->num_players = num_players;
	game->num_team_rocket_left = TEAM_ROCKET_GRUNTS;
	game->num_trainers_left = num_players - TEAM_ROCKET_GRUNTS;
	game->time_of_day = NIGHT;

	gameInitRound(game);

	game->players = gameCreatePlayers(num_players);

	return game;
}

void gameEnd(Game *game)
{
	assert(game != NULL);
	gameDestroyPlayers(game);
	free(game);
}
