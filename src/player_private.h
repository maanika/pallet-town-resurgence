#ifndef _PLAYER_PRIVATE_
#define _PLAYER_PRIVATE_

#include "player.h"

struct PlayerPrivate{
	int pokemon_partner_stolen;
	int can_vote;
};

void playerInit(Player *player, const int player_id, const Role role);

#endif
