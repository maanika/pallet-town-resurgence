#include <stdlib.h>
#include <assert.h>

#include "player.h"
#include "player_private.h"
#include "officer_jenny.h"

OfficerJenny *officerJennyCreate(const int player_id)
{
	OfficerJenny *officer_jenny = malloc(sizeof(OfficerJenny));
	if (!officer_jenny) {
		exit(EXIT_FAILURE);
	}
	playerInit((Player *)officer_jenny, player_id, OFFICER_JENNY);
	return officer_jenny;
}

