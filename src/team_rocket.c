#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "event.h"
#include "player.h"
#include "player_private.h"
#include "team_rocket.h"
#include "util.h"

static void teamRocketPrintRole(const Player *const player)
{
	assert(player != NULL);

	playerShowDefaultSummary(player);
	printf("\nYou are plotting to steal a trainer's Pokemon\n"
	       "\nSelect a trainer's Pokemon to steal?\n");
}

static Event teamRocketSepcialAbility(const Player *const self, const Player *const target_player)
{
    Action action = ACTION_INVALID;

	if (target_player->player_id == self->player_id) {
		printf("\nYou cannot steal your own Pokemon, poor thing! :(\n");

	} else if (playerIsEliminated(target_player)) {
		printf("\nYou already stole their Pokemon -.-\n");

	} else {
		action = ACTION_STEAL_POKEMON;
	}

	const Event event = {.action = action, .targetd_player_id = target_player->player_id};
	return event;
}

static const PlayerSkills team_rocket_skills = {
	.show_summary = teamRocketPrintRole,
	.speical_ability = teamRocketSepcialAbility,
};

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
