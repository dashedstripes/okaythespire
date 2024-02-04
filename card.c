#include <SDL2/SDL.h>
#include "card.h"

const int CARD_WIDTH = 150;
const int CARD_HEIGHT = 200;

int Card_Init(Card *card, int id) 
{
  card->id = id;
  card->x = 0;
  card->y = 0;
  card->w = CARD_WIDTH;
  card->h = CARD_HEIGHT;
  return 0;
}

void Card_Render(SDL_Renderer *renderer, Card *card) {
  SDL_Rect rect = {card->x, card->y, CARD_WIDTH, CARD_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

int Card_Intersect(Card *card, int x, int y) {
  return (x >= card->x && x <= card->x + CARD_WIDTH &&
          y >= card->y && y <= card->y + CARD_HEIGHT);
}