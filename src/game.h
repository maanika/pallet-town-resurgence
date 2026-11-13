#ifndef _GAME_
#define _GAME_

#define MAX_NUM_PLAYERS 10
#define MIN_NUM_PLAYERS 4

typedef struct Game Game;

Game *gameCreate(int num_players);

void gameStart(Game *game);

void gameEnd(Game *game);

#endif /* _GAME_ */
