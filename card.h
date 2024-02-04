#include <SDL2/SDL.h>

typedef struct {
  int id;
  int x;
  int y;
} Card;

void Card_Render(SDL_Renderer *renderer, Card *card);
int Card_Intersect(Card *card, int x, int y);