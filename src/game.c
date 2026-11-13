#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "event.h"
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
	uint8_t pokemon_protected_trainer_ids_flag;
	uint8_t pokemon_stolen_trainer_ids_flag;
	uint8_t voting_list[MAX_NUM_PLAYERS];
	Player **players;
};

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
	if (playerIsEliminated(output_player)) {
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

static void gameHandleEvent(Game *const game, const Event event)
{
	assert(game != NULL);

	switch (event.action) {
	case ACTION_NONE:
		break;
	case ACTION_STEAL_POKEMON:
		game->pokemon_stolen_trainer_ids_flag |= (1U << (event.targetd_player_id));
		break;
	case ACTION_PROTECT_POKEMON:
		game->pokemon_protected_trainer_ids_flag |= (1U << (event.targetd_player_id));
		break;
	case ACTION_INVALID:
		assert(false); // this cannot happen
		break;
	}
}

static void gameShowDayRoundResults(Game *game)
{
	assert(game != NULL);

	int max_num_vote = -1;
	uint8_t max_vote_id = 0;

	for (uint8_t i = 0; i < game->num_players; i++) {
		if (game->voting_list[i] > max_num_vote) {
			max_num_vote = game->voting_list[i];
			max_vote_id = i;
		}
		// If two players recive the same number of votes, flip a coin
		if (game->voting_list[i] == max_num_vote) {
			if (rand() % 2 == 1) {
				max_vote_id = i;
			}
		}
	}

	playerEliminate(game->players[max_vote_id]);
	const int player_id = max_vote_id + 1;
	printf("\nThe town has decided to battle against player %d...\n\nPlayer %d has lost the battle "
	       "and has been eliminated\n",
	       player_id, player_id);
}

static void gameShowNightRoundResults(Game *game)
{
	assert(game != NULL);

	uint8_t pokemon_stolen =
		game->pokemon_stolen_trainer_ids_flag & ~(game->pokemon_protected_trainer_ids_flag);

	printf("\n\n --- The Night has ended and the Day has begun --- \n\n");

	if (pokemon_stolen == 0) {
		printf("\nHooray!!! No Pokemon were stolen tonight! :)\n");
		return;
	}

	for (int i = 0; i < MAX_NUM_PLAYERS; i++) {
		if (pokemon_stolen & (1U << i)) {
			printf("\nSadly player %d had their partner Pokemon stolen by Team Rocket "
			       "and is eliminated\n",
			       i + 1);
			game->num_trainers_left--;
			playerEliminate(game->players[i]);
			break;
		}
	}

	return;
}

static void gamePlayerNightTurn(Game *const game, Player *const current_player)
{
	assert(game != NULL);
	assert(current_player != NULL);

	current_player->skills->show_summary(current_player);

	if (current_player->role == TRAINER) {
		return;
	}

	int target_id = 1;

	if (current_player->role != GYM_LEADER) {
		printf("\nPlayers:");
		for (int i = 0; i < game->num_players; i++) {
			gamePrintPlayer(current_player, game->players[i]);
		}
		printf("\n\n");
	}

	Event event;
	eventSetDefault(&event);

	do {
		if (current_player->role != GYM_LEADER) {
			target_id =
				utilGetValidIntInput("\nEnter target's id? ", 1, game->num_players);
		}
		event = current_player->skills->speical_ability(current_player,
								game->players[target_id - 1]);
	} while (event.action == ACTION_INVALID);

	gameHandleEvent(game, event);

	return;
}

static void gamePlayerVote(Game *const game, Player *const current_payer)
{
	assert(game != NULL);
	assert(current_payer != NULL);

	if (!playerCanVote(current_payer)) {
		return;
	}

	uint8_t vote = 1;
	do {
		const int vote = utilGetValidIntInput(
			"\nDecide which player to have a Pokemon battle with? ", 1,
			game->num_players);
		// canno
		if (playerIsEliminated(game->players[vote - 1])) {
			printf("\nThe selcted player has already had their Pokemon stoled :( and "
			       "is eliminated form the game\n");
			continue;
		}
		if (vote == (current_payer->player_id + 1)) {
			printf("\nYou cannot battle yourself :p\n");
			continue;
		}
		break;
	} while (true);

	game->voting_list[vote - 1]++;
}

static void gameNightRound(Game *const game)
{
	for (int i = 0; i < game->num_players; i++) {
		if (playerIsEliminated(game->players[i])) {
			continue;
		}

		printf("\n---------- It is Night Time! ----------\n\n");
		printf("Player %d\n", i + 1);

		utilPressEnterToContinue("Press ENTER when ready.");

		gamePlayerNightTurn(game, game->players[i]);

		utilPressEnterToContinue("Press ENTER to continue.");
		utilClearScreen();
	}
}

static void gameDayRound(Game *const game)
{
	for (int i = 0; i < game->num_players; i++) {
		if (playerIsEliminated(game->players[i])) {
			continue;
		}
		printf("\n---------- It is Day Time! ----------\n\n");
		printf("Player %d\n", i + 1);
		utilPressEnterToContinue("Press ENTER when ready.");

		gamePlayerVote(game, game->players[i]);

		utilPressEnterToContinue("Press ENTER to continue.");
		utilClearScreen();
	}
}

static void gameResetRound(Game *game)
{
	assert(game != NULL);
	game->pokemon_protected_trainer_ids_flag = 0;
	game->pokemon_stolen_trainer_ids_flag = 0;
	memset(game->voting_list, 0, sizeof(game->voting_list));
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

		gameResetRound(game);
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

	gameResetRound(game);

	game->players = gameCreatePlayers(num_players);

	return game;
}

void gameEnd(Game *const game)
{
	assert(game != NULL);
	gameDestroyPlayers(game);
	free(game);
}
