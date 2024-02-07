#include "enemy.h"
#include "hand.h"
#include "deck.h"

int Enemy_Init(Enemy *enemy) 
{
  enemy->deck = NULL;
  enemy->hand = NULL;
  enemy->health = 100;
  enemy->energy = 3;
  return 0;
}