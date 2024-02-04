#include <SDL2/SDL.h>
#include "card.h"

void Card_Render(SDL_Renderer *renderer, Card *card) {
  SDL_Rect rect = {card->x, card->y, card->width, card->height};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

int Card_Intersect(Card *card, int x, int y) {
  return (x >= card->x && x <= card->x + card->width &&
          y >= card->y && y <= card->y + card->height);
}