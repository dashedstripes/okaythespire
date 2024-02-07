#include <SDL2/SDL.h>
#include "card.h"

int Card_Init(Card *card, int id, enum CardType type, int value) 
{
  card->id = id;
  card->type = type;
  card->value = value;
  return 0;
}

void Card_Render(SDL_Renderer *renderer, Card *card, int x, int y) {
  SDL_Rect rect = {x, y, CARD_WIDTH, CARD_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

int Card_Intersect(Card *card, int x, int y, int cardX, int cardY) 
{
  return (x >= cardX && x <= cardX + CARD_WIDTH &&
          y >= cardY && y <= cardY + CARD_HEIGHT);
}