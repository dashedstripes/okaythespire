#include <SDL2/SDL.h>
#include "card.h"

const int CARD_WIDTH = 150;
const int CARD_HEIGHT = 200;

void Card_Render(SDL_Renderer *renderer, Card *card) {
  // printf("Rendering card at %d, %d, with width+height %d, %d\n", card->x, card->y, card->width, card->height);
  SDL_Rect rect = {card->x, card->y, CARD_WIDTH, CARD_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

int Card_Intersect(Card *card, int x, int y) {
  return (x >= card->x && x <= card->x + CARD_WIDTH &&
          y >= card->y && y <= card->y + CARD_HEIGHT);
}