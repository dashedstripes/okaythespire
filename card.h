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
  enum CardType type;
  int value;
  int cost;
} Card;

struct CardModel {
  float x;
  float y;
  float w;
  float h;
  float vx;
  float vy;
  float cooldown;
  int isAnimating;
};

int Card_Init(Card *card, int id, enum CardType type, int value, int cost);
void Card_MakeActive(Card *card, struct CardModel *model);
void Card_MakeInactive(Card *card, struct CardModel *model);
void Card_Update(Card *card, struct CardModel *model, float deltaTime);
void Card_Render(SDL_Renderer *renderer, Card *card, struct CardModel *model, TTF_Font *font);
int Card_Intersect(Card *card, int x, int y, struct CardModel *model);

#endif