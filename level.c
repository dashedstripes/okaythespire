#include "enemy.h"
#include "player.h"
#include "level.h"
#include "screen.h"
#include <SDL2_ttf/SDL_ttf.h>

int Level_Init(Level *level, Enemy *enemy, Player *player)
{
  level->enemy = enemy;
  level->player = player;
  level->activePlayer = 0; // 0 = player, 1 = enemy
  return 0;
}

int Level_HandleClick(Level *level, int x, int y)
{
  if(level->activePlayer == 0)
  {
    Player_HandleClick(level->player, x, y);
  }
  return 0;
}

int Level_Update(Level *level, float deltaTime)
{
  Player_Update(level->player, deltaTime);
  return 0;
}

int Level_Render(SDL_Renderer *renderer, Level *level, TTF_Font *font)
{
  Enemy_Render(renderer, level->enemy, font);
  Player_Render(renderer, level->player, font);
  return 0;
}