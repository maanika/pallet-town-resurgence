#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "player_private.h"
#include "trainer.h"
#include "util.h"

Trainer *trainerCreate(const int player_id)
{
	Trainer *trainer = malloc(sizeof(Trainer));
	if (!trainer) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)trainer, player_id, TRAINER);
	return trainer;
}

void trainerNightRound(Trainer *const trainer)
{
	printf("\nYou are sleeping with your partner Pokemon\n\n");
}

void trainerDayRound(Trainer *const trainer)
{
	if (trainer->player.private_data->can_vote) {
        // TODO: only alive players can be selected, using 1-10 for now
		const int i = utilGetValidIntInput("Vote who the Team Rocket Grunt may be?", 1, 10);
        (void)i;
	}
	return;
}
