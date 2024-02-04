#include <SDL2/SDL.h>

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Card;

void Card_Render(SDL_Renderer *renderer, Card *card);