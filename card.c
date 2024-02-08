#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "card.h"
#include <SDL2_ttf/SDL_ttf.h>

int Card_Init(Card *card, int id, enum CardType type, int value) 
{
  card->id = id;
  card->type = type;
  card->value = value;

  TTF_Font *font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 64);
  card->font = font;

  return 0;
}

int Card_Cleanup(Card *card)
{
  TTF_CloseFont(card->font);
  return 0;
}

void Card_Render(SDL_Renderer *renderer, Card *card, int x, int y) 
{
  SDL_Rect cardRect = {x, y, CARD_WIDTH, CARD_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &cardRect);

  // render value
  SDL_Rect valueRect = {x + 8, y + 8, 24, 24};
  char valueText[4];
  sprintf(valueText, "%d", card->value);

  SDL_Surface *text = TTF_RenderText_Solid(card->font, valueText, (SDL_Color){255, 255, 255});
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
  SDL_RenderCopy(renderer, texture, NULL, &valueRect);
  SDL_FreeSurface(text);
  SDL_DestroyTexture(texture);

  // render type
  SDL_Rect typeRect = {x + ((CARD_WIDTH - 72) - 8), y + ((CARD_HEIGHT - 24) - 8), 72, 24};
  text = TTF_RenderText_Solid(card->font, card->type == ATTACK_CARD ? "ATTACK" : "BLOCK", (SDL_Color){255, 255, 255});
  texture = SDL_CreateTextureFromSurface(renderer, text);
  SDL_RenderCopy(renderer, texture, NULL, &typeRect);
  SDL_FreeSurface(text);
  SDL_DestroyTexture(texture);
}

int Card_Intersect(Card *card, int x, int y, int cardX, int cardY) 
{
  return (x >= cardX && x <= cardX + CARD_WIDTH &&
          y >= cardY && y <= cardY + CARD_HEIGHT);
}