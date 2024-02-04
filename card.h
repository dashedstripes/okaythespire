#include <SDL2/SDL.h>

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Card;

void Card_Render(SDL_Renderer *renderer, Card *card);
int Card_Intersect(Card *card, int x, int y);