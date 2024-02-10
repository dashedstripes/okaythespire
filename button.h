#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

typedef struct {
  float x;
  float y;
  float w;
  float h;
  char* text;
} Button;

void Button_Init(Button *button, float x, float y, float w, float h, char* text);
int Button_Intersect(Button *button, float x, float y);
void Button_Render(SDL_Renderer *renderer, Button *button, TTF_Font *font);

#endif