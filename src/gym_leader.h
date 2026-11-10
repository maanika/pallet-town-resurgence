#ifndef _GYM_LEADER_
#define _GYM_LEADER_

#include "player.h"

typedef struct {
	Player player;
    int player_id_protect;
} GymLeader;

GymLeader *gymLeaderCreate(const int player_id);

void gymLeaderNightRound(GymLeader *const gym_leader);

#endif
