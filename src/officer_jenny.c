#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "event.h"
#include "player.h"
#include "player_private.h"
#include "officer_jenny.h"

static void officerJennyPrintRole(const Player *const player)
{
	assert(player != NULL);

	playerShowDefaultSummary(player);
	printf("\nYou are on patrol with your partner Pokemon\n"
	       "\nSelect a trainer's Pokemon to protect over night?\n");
}

static Event officerJennySpecialAbility(const Player *const self, const Player *const target_player)
{
	Action action = ACTION_INVALID;

	if (target_player->player_id == self->player_id) {
		printf("\nYou cannot protect yourself :p\n");

	} else if (playerIsEliminated(target_player)) {
		printf("\nSelected player has already had their partner Pokemon stolen\n");

	} else {
		action = ACTION_PROTECT_POKEMON;
	}

	const Event event = {.action = action, .targetd_player_id = target_player->player_id};
	return event;
}

static const PlayerSkills officer_jenny_skills = {
	.show_summary = officerJennyPrintRole,
	.speical_ability = officerJennySpecialAbility,
};

OfficerJenny *officerJennyCreate(const int player_id)
{
	OfficerJenny *officer_jenny = malloc(sizeof(OfficerJenny));
	if (!officer_jenny) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)officer_jenny, player_id, OFFICER_JENNY, &officer_jenny_skills);
	return officer_jenny;
}
