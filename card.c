#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include "card.h"
#include "text.h"
#include "screen.h"

int Card_Init(Card *card, int id, enum CardType type, int value, int cost, CardModel *model)
{
  card->id = id;
  card->type = type;
  card->value = value;
  card->cost = cost;
  card->model = model;
  return 0;
}

void CardModel_Init(CardModel *model)
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

void Card_Toggle(Card *card, int isActive)
{
  if (card->model->isAnimating)
  {
    return;
  }

  if(!card->model->startY)
  {
    card->model->startY = card->model->y;
  }

  if(isActive)
  {
    // move card up
    card->model->nextY = card->model->startY - 50;
  }
  else
  {
    // move card down
    card->model->nextY = card->model->startY;
  }

  card->model->isAnimating = 1;
}

void Card_Update(Card *card, float deltaTime)
{
  if (card->model->isAnimating)
  {
    const float EPSILON = 5.0f;
    if (fabs(card->model->y - card->model->nextY) < EPSILON)
    {
      card->model->y = card->model->nextY;
      card->model->vy = 0;
      card->model->isAnimating = 0;
    }
    else
    {
      if (card->model->y < card->model->nextY)
      {
        card->model->vy = card->model->moveSpeed;
      }
      else if (card->model->y > card->model->nextY)
      {
        card->model->vy = -card->model->moveSpeed;
      }

      card->model->y += card->model->vy * deltaTime;
    }
  }
}

void Card_Render(SDL_Renderer *renderer, Card *card, TTF_Font *font)
{
  SDL_Rect cardRect = {card->model->x, card->model->y, card->model->w, card->model->h};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &cardRect);

  // render value
  char valueText[4];
  sprintf(valueText, "%d", card->value);

  // TTF_SetFontSize(font, 48);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface *valueSurface = Text_Create(font, valueText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, valueSurface, card->model->x + ((CARD_WIDTH / 2) - (valueSurface->w / 2)), card->model->y + (CARD_HEIGHT / 2) - (valueSurface->h / 2));

  // render type
  // TTF_SetFontSize(font, 16);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  SDL_Surface *typeSurface = Text_Create(font, card->type == ATTACK_CARD ? "ATTACK" : "BLOCK", (SDL_Color){255, 255, 255});
  Text_Render(renderer, typeSurface, card->model->x + 16, card->model->y + 16);

  // render mana cost
  char manaText[8];
  sprintf(manaText, "%d mana", card->cost);
  // TTF_SetFontSize(font, 16);
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  SDL_Surface *manaSurface = Text_Create(font, manaText, (SDL_Color){255, 255, 255});
  Text_Render(renderer, manaSurface, card->model->x + CARD_WIDTH - manaSurface->w - 16, card->model->y + CARD_HEIGHT - manaSurface->h - 16);
}

int Card_Intersect(Card *card, float x, float y)
{
  return (x >= card->model->x && x <= card->model->x + card->model->w &&
          y >= card->model->y + card->model->vy && y <= card->model->y + card->model->vy + card->model->h);
}
