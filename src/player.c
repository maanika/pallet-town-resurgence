#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "player.h"
#include "player_private.h"

static PlayerPrivate *playerPrivateCreate(void)
{
	PlayerPrivate *private_data = malloc(sizeof(PlayerPrivate));
	if (!private_data) {
		exit(EXIT_FAILURE);
	}
	private_data->pokemon_partner_stolen = false;
	private_data->can_vote = true;
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
}

void playerDeinit(Player *player) {
    assert(player != NULL);
    playerPrivateDestroy(player);
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
