#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "player.h"
#include "player_private.h"
#include "gym_leader.h"

static void gymLeaderPrintRole(const Player *const player)
{
	printf("Role: Gym Leader\n");
}

static const PlayerSkills gym_leader_skills = {
    .print_role = gymLeaderPrintRole,
};

void gymLeaderNightRound(GymLeader *const gym_leader)
{
	printf("\nYou are sleeping while your partner Pokemon on guard\n");
}

GymLeader *gymLeaderCreate(const int player_id)
{
	GymLeader *gym_leader = malloc(sizeof(GymLeader));
	if (!gym_leader) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)gym_leader, player_id, GYM_LEADER, &gym_leader_skills);
	return gym_leader;
}
