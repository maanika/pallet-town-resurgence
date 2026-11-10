#ifndef _TRAINER_
#define _TRAINER_

#include "player.h"

typedef struct {
	Player player;
} Trainer;

Trainer *trainerCreate(const int player_id);

void trainerNightRound(Trainer *const trainer);

#endif
