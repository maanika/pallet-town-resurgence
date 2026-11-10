#include <stdlib.h>
#include <assert.h>

#include "player.h"
#include "player_private.h"
#include "gym_leader.h"
#include "util.h"

GymLeader *gymLeaderCreate(const int player_id)
{
	GymLeader *gym_leader = malloc(sizeof(GymLeader));
	if (!gym_leader) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)gym_leader, player_id, GYM_LEADER);
	return gym_leader;
}

void gymLeaderNightRound(GymLeader *const gym_leader)
{
    // TODO: only alive players can be selected, using 1-10 for now
	const int i = utilGetValidIntInput("Select a player to protect over night?", 1, 10);
    (void)i;
}
