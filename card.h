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
  int vy;
  enum CardType type;
  int value;
  int cost;
  SDL_Texture *texture;
  char *texturePath;
} Card;

int Card_Init(Card *card, int id, enum CardType type, int value, int cost);
void Card_Update(Card *card, float deltaTime);
void Card_Render(SDL_Renderer *renderer, Card *card, int x, int y, TTF_Font *font);
int Card_Intersect(Card *card, int x, int y, int cardX, int cardY);

#endif