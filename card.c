#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "card.h"
#include <SDL2_ttf/SDL_ttf.h>
#include "text.h"

int Card_Init(Card *card, int id, enum CardType type, int value) 
{
  card->id = id;
  card->type = type;
  card->value = value;
  card->font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 64);
  return 0;
}

void Card_Render(SDL_Renderer *renderer, Card *card, int x, int y) 
{
  SDL_Rect cardRect = {x, y, CARD_WIDTH, CARD_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &cardRect);

  // render value
  char valueText[4];
  sprintf(valueText, "%d", card->value);

  TTF_SetFontSize(card->font, 48);
  TTF_SetFontStyle(card->font, TTF_STYLE_BOLD);
  SDL_Surface *valueSurface = Text_Create(card->font, valueText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, valueSurface, x + ((CARD_WIDTH / 2) - (valueSurface->w / 2)), y + (CARD_HEIGHT / 2) - (valueSurface->h / 2));

  // // render type
  TTF_SetFontSize(card->font, 16);
  SDL_Surface *typeSurface = Text_Create(card->font, card->type == ATTACK_CARD ? "ATTACK" : "BLOCK", (SDL_Color){255, 255, 255});
  Text_Render(renderer, typeSurface, x + ((CARD_WIDTH / 2) - (typeSurface->w / 2)), y + (CARD_HEIGHT / 2) - (typeSurface->h / 2) + 48);
}

int Card_Intersect(Card *card, int x, int y, int cardX, int cardY) 
{
  return (x >= cardX && x <= cardX + CARD_WIDTH &&
          y >= cardY && y <= cardY + CARD_HEIGHT);
}