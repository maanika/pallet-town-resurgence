#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "player.h"
#include "player_private.h"
#include "team_rocket.h"
#include "util.h"

static void teamRocketPrintRole(const Player *const player)
{
    printf("Role: Team Rocket\n");
}

static const PlayerSkills team_rocket_skills = {
    .print_role = teamRocketPrintRole,
};

void teamRocketNightRound(TeamRocket *const team_rocket)
{
	// TODO: only alive players can be selected, using 1-10 for now
	const int i =
		utilGetValidIntInput("Select a player's Pokemon to steal over night? ", 1, 10);
	(void)i;
}

void teamRocketPrint(TeamRocket *const team_rocket)
{
	printf(" [team rocket] ");
}

TeamRocket *teamRocketCreate(const int player_id)
{
	TeamRocket *team_rocket = malloc(sizeof(TeamRocket));
	if (!team_rocket) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)team_rocket, player_id, TEAM_ROCKET_GRUNT, &team_rocket_skills);
	return team_rocket;
}
