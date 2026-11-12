#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "player.h"
#include "player_private.h"
#include "gym_leader.h"

static void gymLeaderShowSummary(const Player *const player)
{
    assert(player != NULL);

    playerShowDefaultSummary(player);
	printf("\nYou are sleeping while your partner Pokemon is on guard\n");
}

// static void gymLeaderSecialAbility(GymLeader *const gym_leader)
// {
//     // can survive if Pokemon partner is stronger that team rockets Pokemon
//     return;
// }

static const PlayerSkills gym_leader_skills = {
    .show_summary = gymLeaderShowSummary,
};

GymLeader *gymLeaderCreate(const int player_id)
{
	GymLeader *gym_leader = malloc(sizeof(GymLeader));
	if (!gym_leader) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)gym_leader, player_id, GYM_LEADER, &gym_leader_skills);
	return gym_leader;
}
