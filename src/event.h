#ifndef _EVENT_
#define _EVENT_

typedef enum {
	ACTION_NONE,
	ACTION_STEAL_POKEMON,
	ACTION_PROTECT_POKEMON,
} Action;

typedef struct {
	int targetd_player_id;
	Action action;
} Event;

void eventSetDefault(Event *event);

#endif
