#ifndef _TEAM_ROCKET_
#define _TEAM_ROCKET_

#include "player.h"

typedef struct {
	Player player;
} TeamRocket;

TeamRocket *teamRocketCreate(const int player_id);

#endif
