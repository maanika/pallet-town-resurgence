#ifndef _TEAM_ROCKET_
#define _TEAM_ROCKET_

#include "player.h"

typedef struct {
	Player player;
} TeamRocket;

TeamRocket *teamRocketCreate(const int player_id);

void teamRocketNightRound(TeamRocket *const team_rocket);

void teamRocketPrint(TeamRocket *const team_rocket);

#endif
