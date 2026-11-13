#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "player.h"
#include "player_private.h"
#include "trainer.h"
#include "event.h"

static void trainerPrintRole(const Player *const player)
{
	assert(player != NULL);

	playerShowDefaultSummary(player);
	printf("\nYou are fast asleep with your partner Pokemon\n");
}

static Event trainerSpecialAbility(const Player *const self, const Player *const target_player)
{
    Event event;
    eventSetDefault(&event);
    return event;
}

static const PlayerSkills trainer_skills = {
	.show_summary = trainerPrintRole,
	.speical_ability = trainerSpecialAbility,
};

Trainer *trainerCreate(const int player_id)
{
	Trainer *trainer = malloc(sizeof(Trainer));
	if (!trainer) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)trainer, player_id, TRAINER, &trainer_skills);
	return trainer;
}
