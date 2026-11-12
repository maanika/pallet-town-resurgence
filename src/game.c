#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "team_rocket.h"
#include "game.h"
#include "util.h"

#define TEAM_ROCKET_GRUNTS 1

typedef enum {
	DAY_TIME,
	NIGHT_TIME,
} TimeOfDay;

typedef enum {
	GAME_WINNER_NONE,
	GAME_WINNER_TEAM_ROCKET,
	GAME_WINNER_TOWN_SAVED,
} GameWinner;

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

static void gameInitRound(Game *const game)
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

static void gameDestroyPlayers(Game *const game)
{
	for (int i = 0; i < game->num_players; i++) {
		playerDeinit(game->players[i]);
	}
	free(game->players);
}

static GameWinner gameGetWinner(const Game *const game)
{
	if (game->num_team_rocket_left >= game->num_trainers_left) {
		return GAME_WINNER_TEAM_ROCKET;
	} else if (game->num_team_rocket_left == 0) {
		return GAME_WINNER_TOWN_SAVED;
	}
	return GAME_WINNER_NONE;
}

static void gameSetNextTimeOfDay(Game *const game)
{
	game->time_of_day = ((game->time_of_day) == NIGHT_TIME ? DAY_TIME : NIGHT_TIME);
}

static void gamePrintPlayer(Player *const current_player, Player *const output_player)
{
	// Output Player
	if (!playerIsAlive(output_player)) {
		return;
	}
	printf("\n* Player %d ", output_player->player_id + 1);
	if (output_player->player_id == current_player->player_id) {
		printf("[you] ");
	}
	// Expose team rocket grunts only to other team rocket grunts
	if ((current_player->role == TEAM_ROCKET_GRUNT) &&
	    (output_player->role == TEAM_ROCKET_GRUNT)) {
		teamRocketPrint((TeamRocket *)current_player);
	}
}

static void gamePlayerTurn(Game *const game, Player *const current_player)
{
	current_player->skills->show_summary(current_player);

	if (current_player->role == TRAINER || current_player->role == GYM_LEADER) {
		goto skip_print_players;
	}

	// Print list of players alive
	printf("\nPlayers:");
	for (int i = 0; i < game->num_players; i++) {
		gamePrintPlayer(current_player, game->players[i]);
	}
	printf("\n\n");

skip_print_players:

	return;
}

static void gameNightRound(Game *const game)
{
	for (int i = 0; i < game->num_players; i++) {
		if (!playerIsAlive(game->players[i])) {
			continue;
		}

		printf("\n---------- It is Night Time! ----------\n\n");
		printf("Player %d\n", i + 1);

		utilPressEnterToContinue("Press ENTER when ready.");

		gamePlayerTurn(game, game->players[i]);

		utilPressEnterToContinue("Press ENTER to continue.");
		utilClearScreen();
	}
}

static void gameShowNightRoundResults(Game *game)
{
	return;
}

static void gameDayRound(Game *const game)
{
	for (int i = 0; i < game->num_players; i++) {
		printf("\n---------- It is Day Time! ----------\n\n");
		printf("Player %d\n", i + 1);
		utilPressEnterToContinue("Press ENTER when ready.");
		utilPressEnterToContinue("Press ENTER to continue.");
		utilClearScreen();
	}
}

static void gameShowDayRoundResults(Game *game)
{
	return;
}

void gameStart(Game *const game)
{
	assert(game != NULL);

	while (gameGetWinner(game) == GAME_WINNER_NONE) {
		utilPressEnterToContinue("Press ENTER to continue.");
		utilClearScreen();

		if (game->time_of_day == NIGHT_TIME) {
			gameNightRound(game);
			gameShowNightRoundResults(game);

		} else {
			gameDayRound(game);
			gameShowDayRoundResults(game);
		}

		gameSetNextTimeOfDay(game);
	}

	printf("\n\n%s\n\n", gameGetWinner(game) == GAME_WINNER_TOWN_SAVED
				     ? "Pallet Town is Saved :) !!!!"
				     : "Team Rocket Wins :( ....");
	return;
}

Game *gameCreate(const int num_players)
{
	Game *game = malloc(sizeof(Game));
	if (!game) {
		exit(EXIT_FAILURE);
	}
	game->num_players = num_players;
	game->num_team_rocket_left = TEAM_ROCKET_GRUNTS;
	game->num_trainers_left = num_players - TEAM_ROCKET_GRUNTS;
	game->time_of_day = NIGHT_TIME;

	gameInitRound(game);

	game->players = gameCreatePlayers(num_players);

	return game;
}

void gameEnd(Game *const game)
{
	assert(game != NULL);
	gameDestroyPlayers(game);
	free(game);
}
