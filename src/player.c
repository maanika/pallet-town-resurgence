#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "player.h"
#include "player_private.h"
#include "gym_leader.h"
#include "trainer.h"
#include "officer_jenny.h"
#include "team_rocket.h"

static PlayerPrivate *playerPrivateCreate(void)
{
	PlayerPrivate *private_data = malloc(sizeof(PlayerPrivate));
	if (!private_data) {
		exit(EXIT_FAILURE);
	}
	return private_data;
}

static void playerPrivateDestroy(Player *player)
{
	assert(player != NULL);
	free(player->private_data);
}

// Initialisatuin function -> i.e base class constructor
void playerInit(Player *player, const int player_id, const Role role)
{
	assert(player != NULL);
	player->player_id = player_id;
	player->role = role;
	player->private_data = playerPrivateCreate();
	player->private_data->pokemon_partner_stolen = false;
	player->private_data->can_vote = true;
	player->private_data->is_alive = true;
}

void playerDeinit(Player *player)
{
	assert(player != NULL);
	playerPrivateDestroy(player);
    free(player);
}

void playerReset(Player *player)
{
	assert(player != NULL);
	player->private_data->can_vote = true;
	player->private_data->pokemon_partner_stolen = false;
}

bool playerPokemonStolen(const Player *player)
{
	assert(player != NULL);
	return player->private_data->pokemon_partner_stolen;
}

bool playerCanVote(const Player *player)
{
	assert(player != NULL);
	return player->private_data->can_vote;
}

bool playerIsAlive(const Player *const player)
{
    return player->private_data->is_alive;
}

void playerBanVote(Player *player)
{
	assert(player != NULL);
	player->private_data->can_vote = false;
}

const char *playerRoleToString(const Role role)
{
	switch (role) {
	case TEAM_ROCKET_GRUNT:
		return "Team Rocket Grunt";
	case TRAINER:
		return "Trainer";
	case GYM_LEADER:
		return "Gym Leader";
	case OFFICER_JENNY:
		return "Officer Jenny";
	case ROLE_COUNT:
		break;
	}
	// should not reach here
	assert(false);
	return NULL;
}

void playerNightRound(Player *const player)
{
	switch (player->role) {
	case TEAM_ROCKET_GRUNT:
        return teamRocketNightRound((TeamRocket *)player);
	case TRAINER:
        return trainerNightRound((Trainer *)player);
	case GYM_LEADER:
		return gymLeaderNightRound((GymLeader *)player);
	case OFFICER_JENNY:
		return officerJennyNightRound((OfficerJenny *)player);
	case ROLE_COUNT:
		break;
	}
	// should not reach here
	assert(false);
	return;
}

// TODO: Duplication, can refactor with above function?
void playerDayRound(Player *const player)
{
	switch (player->role) {
	case TEAM_ROCKET_GRUNT:
        return;
	case TRAINER:
        return;
	case GYM_LEADER:
		return;
	case OFFICER_JENNY:
		return;
	case ROLE_COUNT:
		break;
	}
	// should not reach here
	assert(false);
	return;
}

Player *playerCreate(const int player_id, const Role role)
{
	Player *player = NULL;
	switch (role) {
	case GYM_LEADER:
		player = (Player *)gymLeaderCreate(player_id);
		break;
	case TEAM_ROCKET_GRUNT:
		player = (Player *)teamRocketCreate(player_id);
		break;
	case TRAINER:
		player = (Player *)trainerCreate(player_id);
		break;
	case OFFICER_JENNY:
		player = (Player *)officerJennyCreate(player_id);
		break;
	case ROLE_COUNT:
		// TODO: better error handling
		assert(false); // should not be able to reach here
		break;
	}

	return player;
}

