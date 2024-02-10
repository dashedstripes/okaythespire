#include "enemy.h"
#include "player.h"
#include "level.h"
#include "hand.h"
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

  // check if a card was clicked
  for (int i = 0; i < level->player->hand->size; i++)
  {
    if (level->player->hand->cards[i] != NULL)
    {
      if (Card_Intersect(level->player->hand->cards[i], x, y, level->player->hand->models[i]))
      {
        if(level->player->hand->activeCard != level->player->hand->cards[i] && level->player->energy >= level->player->hand->cards[i]->cost)
        {
          Hand_MakeActive(level->player->hand, i);
          Card_Toggle(level->player->hand->cards[i], level->player->hand->models[i], 1);
        } else {
          Hand_MakeInactive(level->player->hand, i);
          Hand_DeactivateAllCards(level->player->hand);
        }
      }
    }
  }

  // check if the hand button was clicked
  if(level->player->hand->activeCard != NULL && level->player->energy >= level->player->hand->activeCard->cost)
  {
    if(Button_Intersect(level->player->hand->button, x, y))
    {
      Player_UseCard(level->player, level->enemy);
      Hand_RemoveCard(level->player->hand, level->player->hand->activeCard);
      Hand_DeactivateAllCards(level->player->hand);
    }
  }
  return 0;
}

int Level_Update(Level *level, float deltaTime)
{
  Hand_Update(level->player->hand, deltaTime);
  return 0;
}

int Level_Render(SDL_Renderer *renderer, Level *level, TTF_Font *font)
{
  Enemy_Render(renderer, level->enemy, font);
  Player_Render(renderer, level->player, font);
  Hand_Render(renderer, level->player->hand, (SCREEN_WIDTH / 2) - (((CARD_WIDTH * level->player->hand->size) + (HAND_MARGIN * (level->player->hand->size - 1))) / 2), SCREEN_HEIGHT - CARD_HEIGHT - 20, font);
  return 0;
}