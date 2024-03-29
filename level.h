#include "enemy.h"
#include "player.h"

typedef struct {
  Enemy *enemy;
  Player *player;
  int activePlayer;
} Level;

int Level_Init(Level *level, Enemy *enemy, Player *player);
int Level_Update(Level *level, float deltaTime);
int Level_HandleClick(Level *level, int x, int y);
int Level_Render(SDL_Renderer *renderer, Level *level, TTF_Font *font);