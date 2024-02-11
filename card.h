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
  float x;
  float y;
  float w;
  float h;
  float vx;
  float vy;
  float cooldown;
  int isAnimating;
  float startY;
  float nextY;
  float moveSpeed;
} CardModel;

typedef struct {
  int id;
  enum CardType type;
  int value;
  int cost;
  CardModel *model;
} Card;

int Card_Init(Card *card, int id, enum CardType type, int value, int cost, CardModel *model);
void Card_Update(Card *card, float deltaTime);
void Card_Render(SDL_Renderer *renderer, Card *card, TTF_Font *font);
int Card_Intersect(Card *card, float x, float y);
void CardModel_Init(CardModel *model);
void Card_Toggle(Card *card, int isActive);

#endif