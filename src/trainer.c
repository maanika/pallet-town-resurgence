#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "player.h"
#include "player_private.h"
#include "trainer.h"

static void trainerPrintRole(const Player *const player)
{
    assert(player != NULL);

    playerShowDefaultSummary(player);
	printf("\nYou are fast asleep with your partner Pokemon\n");
}

// static void trainerSpecialAbility(Trainer *const trainer)
// {
//     // none
//     return;
// }

static const PlayerSkills trainer_skills = {
    .show_summary = trainerPrintRole,
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
