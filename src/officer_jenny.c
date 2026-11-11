#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "player.h"
#include "player_private.h"
#include "officer_jenny.h"
#include "util.h"

static void officerJennyPrintRole(const Player *const player)
{
	printf("Role: Officer Jenny\n");
}

static const PlayerSkills officer_jenny_skills = {
    .print_role = officerJennyPrintRole,
};

void officerJennyNightRound(OfficerJenny *const officer_jenny)
{
	const int i =
		utilGetValidIntInput("\nSelect a player's Pokemon to protect over night? ", 1, 10);
	(void)i;
}

OfficerJenny *officerJennyCreate(const int player_id)
{
	OfficerJenny *officer_jenny = malloc(sizeof(OfficerJenny));
	if (!officer_jenny) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)officer_jenny, player_id, OFFICER_JENNY, &officer_jenny_skills);
	return officer_jenny;
}
