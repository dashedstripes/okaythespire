#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "button.h"
#include "text.h"

void Button_Init(Button *button, float x, float y, float w, float h, char* text)
{
  button->x = x;
  button->y = y;
  button->w = w;
  button->h = h;
  button->text = text;
}

int Button_Intersect(Button *button, float x, float y)
{
  if (x > button->x && x < button->x + button->w && y > button->y && y < button->y + button->h)
  {
    return 1;
  }
  return 0;
}

void Button_Render(SDL_Renderer *renderer, Button *button, TTF_Font *font)
{
  SDL_Rect rect = { button->x, button->y, button->w, button->h };
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawRect(renderer, &rect);

  SDL_Surface *text = Text_Create(font, button->text, (SDL_Color){255, 255, 255, 255});
  Text_Render(renderer, text, button->x + button->w / 2 - text->w / 2, button->y + button->h / 2 - text->h / 2);
}