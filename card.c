#include <SDL2/SDL.h>
#include "card.h"

void Card_Render(SDL_Renderer *renderer, Card *card) {
  SDL_Rect rect = {card->x, card->y, card->width, card->height};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}