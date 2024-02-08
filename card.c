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
  Text_Render(renderer, card->font, valueText, x + ((CARD_WIDTH / 2) - 16), y + ((CARD_HEIGHT / 2) - 48), (SDL_Color){255, 255, 255});

  // render type
  TTF_SetFontSize(card->font, 16);
  Text_Render(renderer, card->font, card->type == ATTACK_CARD ? "ATTACK" : "BLOCK", x + ((CARD_WIDTH / 2) - 32), y + (CARD_HEIGHT - 32), (SDL_Color){255, 255, 255});
}

int Card_Intersect(Card *card, int x, int y, int cardX, int cardY) 
{
  return (x >= cardX && x <= cardX + CARD_WIDTH &&
          y >= cardY && y <= cardY + CARD_HEIGHT);
}