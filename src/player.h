#ifndef _PLAYER_
#define _PLAYER_

#include <stdbool.h>

typedef enum {
	TEAM_ROCKET_GRUNT,
	TRAINER,
	GYM_LEADER,
	OFFICER_JENNY,
	ROLE_COUNT,
} Role;

typedef struct PlayerPrivate PlayerPrivate;

typedef struct {
	int player_id;
	Role role;
    PlayerPrivate *private_data;
} Player;

Player *playerCreate(const int player_id, const Role role);

void playerReset(Player *player);

bool playerPokemonStolen(const Player *player);

bool playerIsAlive(const Player *const player);

bool playerCanVote(const Player *player);

void playerBanVote(Player *player);

const char *playerRoleToString(const Role role);

void playerDeinit(Player *player);

void playerNightRound(Player *const player);

void playerDayRound(Player *const player);

#endif
