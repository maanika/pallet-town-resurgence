#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

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

// Initialisatuin function -> i.e base class constructor
void playerInit(Player *player, const int player_id, const Role role, const PlayerSkills *skills)
{
	assert(player != NULL);
	player->player_id = player_id;
	player->role = role;
    player->skills = skills;
	player->private_data = playerPrivateCreate();
	player->private_data->pokemon_partner_stolen = false;
	if (role == TEAM_ROCKET_GRUNT) {
        player->private_data->can_vote = false;
    } else {
        player->private_data->can_vote = true;
    }
	player->private_data->is_elimiated = false;
}

void playerDeinit(Player *player)
{
	assert(player != NULL);
	free(player->private_data);
	free(player);
}

void playerReset(Player *player)
{
	assert(player != NULL);
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

bool playerIsEliminated(const Player *const player)
{
	return player->private_data->is_elimiated;
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

void playerShowDefaultSummary(const Player *const player)
{
    assert(player != NULL);
    printf("\nRole: %s\n", playerRoleToString(player->role));
    // TODO :ASCII art / Graphics here
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
