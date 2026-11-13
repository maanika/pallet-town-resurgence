#ifndef _GYM_LEADER_
#define _GYM_LEADER_

#include "player.h"

typedef struct {
	Player player;
} GymLeader;

GymLeader *gymLeaderCreate(const int player_id);

#endif
