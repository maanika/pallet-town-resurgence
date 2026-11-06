#include <stdlib.h>
#include <assert.h>

#include "player.h"
#include "player_private.h"
#include "team_rocket.h"

TeamRocket *teamRocketCreate(const int player_id)
{
	TeamRocket *team_rocket = malloc(sizeof(TeamRocket));
	if (!team_rocket) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)team_rocket, player_id, TEAM_ROCKET_GRUNT);
	return team_rocket;
}

