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

static void officerJennySetLastProtectedPlayerID(OfficerJenny *officer_jenny, const int id)
{
	assert(officer_jenny != NULL);
	officer_jenny->previous_protected_player_id = id;
}

static bool officerJennyPlayerAlreadyProtected(OfficerJenny *officer_jenny, const int id)
{
	return (officer_jenny->previous_protected_player_id == id);
}

static Event officerJennySpecialAbility(const Player *const self, const Player *const target_player)
{
	Action action = ACTION_INVALID;

	if (target_player->player_id == self->player_id) {
		printf("\nYou cannot protect yourself :p\n");

	} else if (playerIsEliminated(target_player)) {
		printf("\nSelected player has already had their partner Pokemon stolen\n");

	} else if (officerJennyPlayerAlreadyProtected((OfficerJenny *)self,
						      target_player->player_id)) {
		printf("\nYou cannot protect the same player for two nights in a row.");

	} else {
		action = ACTION_PROTECT_POKEMON;
	}

	const Event event = {.action = action, .targetd_player_id = target_player->player_id};
	officerJennySetLastProtectedPlayerID((OfficerJenny *)self, target_player->player_id);

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
	officer_jenny->previous_protected_player_id = -1;
	return officer_jenny;
}
