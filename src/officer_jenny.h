#ifndef _OFFICER_JENNY_
#define _OFFICER_JENNY_

#include "player.h"

typedef struct {
	Player player;
} OfficerJenny;

OfficerJenny *officerJennyCreate(const int player_id);

#endif
