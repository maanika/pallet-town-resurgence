#include <assert.h>
#include <stdlib.h>

#include "event.h"

void eventSetDefault(Event *event) {
    assert(event != NULL);
    event->action = ACTION_NONE;
    event->targetd_player_id = -1;
}
