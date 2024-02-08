#ifndef CARD_H
#define CARD_H

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#define CARD_WIDTH 150
#define CARD_HEIGHT 200

enum CardType {
  ATTACK_CARD,
  BLOCK_CARD
};

typedef struct {
  int id;
  int x;
  int y;
  int w;
  int h;
  enum CardType type;
  int value;
  SDL_Texture *texture;
  char *texturePath;
  TTF_Font *font;
} Card;

int Card_Init(Card *card, int id, enum CardType type, int value);
int Card_Cleanup(Card *card);
void Card_Render(SDL_Renderer *renderer, Card *card, int x, int y);
int Card_Intersect(Card *card, int x, int y, int cardX, int cardY);

#endif