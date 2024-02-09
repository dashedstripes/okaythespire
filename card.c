#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "card.h"
#include <SDL2_ttf/SDL_ttf.h>
#include "text.h"

int Card_Init(Card *card, int id, enum CardType type, int value, int cost) 
{
  card->id = id;
  card->type = type;
  card->value = value;
  card->cost = cost;
  return 0;
}

void CardModel_Init(struct CardModel *model) 
{
  model->x = 0;
  model->y = 0;
  model->w = CARD_WIDTH;
  model->h = CARD_HEIGHT;
  model->vx = 0;
  model->vy = 0;
  model->cooldown = 0;
  model->isAnimating = 0;
  model->startY = 0;
  model->nextY = 0;
  model->moveSpeed = 400;
}

void Card_Toggle(Card *card, struct CardModel *model) 
{
  if(!model->startY) 
  {
    model->startY = model->y;
  }

  if (model->isAnimating) 
  {
    return;
  }

  if (model->y == model->startY) 
  {
    model->nextY = model->startY - 50;
  } 
  else 
  {
    model->nextY = model->startY;
  }

  model->isAnimating = 1;
}

void Card_Update(Card *card, struct CardModel *model, float deltaTime) 
{
  if (model->isAnimating) 
  {
    if (model->y >= model->nextY) 
    {
      model->vy = -model->moveSpeed;
    } 
    else if (model->y <= model->nextY) 
    {
      model->vy = model->moveSpeed;
    }

    model->y += model->vy * deltaTime;

    if((int)model->y == (int)model->nextY) 
    {
      model->y = model->nextY;
      model->vy = 0;
      model->isAnimating = 0;
    }
  }
}

void Card_Render(SDL_Renderer *renderer, Card *card, struct CardModel *model, TTF_Font *font) 
{
  SDL_Rect cardRect = {model->x, model->y, model->w, model->h};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &cardRect);

  // render value
  char valueText[4];
  sprintf(valueText, "%d", card->value);

  TTF_SetFontSize(font, 48);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface *valueSurface = Text_Create(font, valueText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, valueSurface, model->x + ((CARD_WIDTH / 2) - (valueSurface->w / 2)), model->y + (CARD_HEIGHT / 2) - (valueSurface->h / 2));

  // render type
  TTF_SetFontSize(font, 16);
  SDL_Surface *typeSurface = Text_Create(font, card->type == ATTACK_CARD ? "ATTACK" : "BLOCK", (SDL_Color){255, 255, 255});
  Text_Render(renderer, typeSurface, model->x + 16, model->y + 16);

  // render mana cost
  char manaText[8];
  sprintf(manaText, "%d mana", card->cost);
  TTF_SetFontSize(font, 16);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Surface *manaSurface = Text_Create(font, manaText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, manaSurface, model->x + CARD_WIDTH - manaSurface->w - 16, model->y + CARD_HEIGHT - manaSurface->h - 16);
}

int Card_Intersect(Card *card, float x, float y, struct CardModel *model) 
{
  return (x >= model->x && x <= model->x + model->w &&
          y >= model->y + model->vy && y <= model->y + model->vy + model->h);
}