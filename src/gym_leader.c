#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "player.h"
#include "player_private.h"
#include "gym_leader.h"
#include "event.h"

static void gymLeaderShowSummary(const Player *const player)
{
	assert(player != NULL);

	playerShowDefaultSummary(player);
	printf("\nYou are sleeping while your partner Pokemon is on guard\n");
}

static Event gymLeaderSecialAbility(const Player *const self, const Player *const target)
{
	(void)target; // because the gym leader protect themseleves
	assert(self != NULL);

	const Action action = ((rand() % 2) == 1) ? ACTION_PROTECT_POKEMON : ACTION_NONE;

	const Event event = {.action = action, .targetd_player_id = self->player_id};
	return event;
}

static const PlayerSkills gym_leader_skills = {
	.show_summary = gymLeaderShowSummary,
	.speical_ability = gymLeaderSecialAbility,
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
