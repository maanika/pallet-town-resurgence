#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "player.h"
#include "player_private.h"
#include "gym_leader.h"

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
    printf("\nYou are sleeping while your partner Pokemon on guard\n");
}
