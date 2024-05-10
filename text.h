#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN
#include <SDL_ttf.h>
#else
#include <SDL2_ttf/SDL_ttf.h>
#endif

SDL_Surface* Text_Create(TTF_Font *font, const char *text, SDL_Color color);
int Text_Render(SDL_Renderer *renderer, SDL_Surface *surface, int x, int y);

#endif
