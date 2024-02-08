#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

int Text_Render(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, SDL_Color color);

#endif