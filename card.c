#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "card.h"

int Card_Init(Card *card, int id, enum CardType type, int value, char *texturePath) 
{
  card->id = id;
  card->type = type;
  card->value = value;
  card->texturePath = texturePath;
  return 0;
}

int Card_LoadTexture(SDL_Renderer *renderer, Card *card) 
{
  SDL_Surface* imageSurface = IMG_Load(card->texturePath);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  card->texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
  SDL_FreeSurface(imageSurface);
  return 0;
}

void Card_Render(SDL_Renderer *renderer, Card *card, int x, int y) 
{
  SDL_Rect rect = {x, y, CARD_WIDTH, CARD_HEIGHT};
  SDL_RenderCopy(renderer, card->texture, NULL, &rect);
}

int Card_Intersect(Card *card, int x, int y, int cardX, int cardY) 
{
  return (x >= cardX && x <= cardX + CARD_WIDTH &&
          y >= cardY && y <= cardY + CARD_HEIGHT);
}