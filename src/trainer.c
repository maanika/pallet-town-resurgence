#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "player_private.h"
#include "trainer.h"

static void trainerPrintRole(const Player *const player)
{
	printf("Role: Trainer\n");
}

static const PlayerSkills trainer_skills = {
    .print_role = trainerPrintRole,
};

void trainerNightRound(Trainer *const trainer)
{
	printf("\nYou are sleeping with your partner Pokemon\n\n");
}

Trainer *trainerCreate(const int player_id)
{
	Trainer *trainer = malloc(sizeof(Trainer));
	if (!trainer) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)trainer, player_id, TRAINER, &trainer_skills);
	return trainer;
}
