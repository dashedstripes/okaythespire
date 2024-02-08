#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

SDL_Surface* Text_Create(TTF_Font *font, const char *text, SDL_Color color)
{
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
  return surface;
}

int Text_Render(SDL_Renderer *renderer, SDL_Surface *surface, int x, int y)
{
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect rect = {x, y, surface->w, surface->h};
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  return 0;
}