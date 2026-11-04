#ifndef _GAME_
#define _GAME_

typedef struct Game Game;

Game *gameCreate(int num_players);

void gameStart(Game *game);

void gameEnd(Game *game);

#endif /* _GAME_ */
