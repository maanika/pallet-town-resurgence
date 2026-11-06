#include <stdlib.h>
#include <assert.h>

#include "player_private.h"
#include "trainer.h"

Trainer *trainerCreate(const int player_id)
{
	Trainer *trainer = malloc(sizeof(Trainer));
	if (!trainer) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)trainer, player_id, TRAINER);
	return trainer;
}

