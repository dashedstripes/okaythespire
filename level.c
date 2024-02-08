#include "enemy.h"
#include "player.h"
#include "level.h"
#include "hand.h"
#include "screen.h"

int Level_Init(Level *level, Enemy *enemy, Player *player)
{
  level->enemy = enemy;
  level->player = player;
  return 0;
}

int Level_Update(Level *level)
{
  if (level->enemy->health <= 0)
  {
    return 1;
  }
  if (level->player->health <= 0)
  {
    return -1;
  }
  return 0;
}

int Level_HandleClick(Level *level, int x, int y)
{
  for (int i = 0; i < level->player->hand->max_size; i++)
  {
    if (level->player->hand->cards[i] != NULL)
    {
      if (Card_Intersect(
              level->player->hand->cards[i],
              x,
              y,
              (SCREEN_WIDTH / 2) - (((CARD_WIDTH * level->player->hand->size) + (HAND_MARGIN * (level->player->hand->size - 1))) / 2) + (i * (CARD_WIDTH + HAND_MARGIN)),
              SCREEN_HEIGHT - CARD_HEIGHT - 20))
      {
        Player_UseCard(level->player, i, level->enemy);
      }
    }
  }
  return 0;
}

int Level_Render(SDL_Renderer *renderer, Level *level)
{
  Enemy_Render(renderer, level->enemy);
  Player_Render(renderer, level->player);
  Hand_Render(renderer, level->player->hand, (SCREEN_WIDTH / 2) - (((CARD_WIDTH * level->player->hand->size) + (HAND_MARGIN * (level->player->hand->size - 1))) / 2), SCREEN_HEIGHT - CARD_HEIGHT - 20);
  return 0;
}