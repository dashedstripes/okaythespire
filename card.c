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

void Card_Update(Card *card, struct CardModel *model, float deltaTime) 
{
  model->y += model->vy * deltaTime;
}

void Card_Render(SDL_Renderer *renderer, Card *card, struct CardModel *model, TTF_Font *font) 
{
  SDL_Rect cardRect = {model->x, model->y, model->w, model->h};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &cardRect);

  // // render value
  // char valueText[4];
  // sprintf(valueText, "%d", card->value);

  // TTF_SetFontSize(font, 48);
  // TTF_SetFontStyle(font, TTF_STYLE_BOLD);
  // SDL_Surface *valueSurface = Text_Create(font, valueText, (SDL_Color){255, 255, 255});
  // Text_Render(renderer, valueSurface, x + ((CARD_WIDTH / 2) - (valueSurface->w / 2)), card->y + (CARD_HEIGHT / 2) - (valueSurface->h / 2));

  // // // render type
  // TTF_SetFontSize(font, 16);
  // SDL_Surface *typeSurface = Text_Create(font, card->type == ATTACK_CARD ? "ATTACK" : "BLOCK", (SDL_Color){255, 255, 255});
  // Text_Render(renderer, typeSurface, x + 16, card->y + 16);

  // // render mana cost
  // char manaText[8];
  // sprintf(manaText, "%d mana", card->cost);
  // TTF_SetFontSize(font, 16);
  // TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
  // SDL_Surface *manaSurface = Text_Create(font, manaText, (SDL_Color){255, 255, 255});
  // Text_Render(renderer, manaSurface, x + CARD_WIDTH - manaSurface->w - 16, card->y + CARD_HEIGHT - manaSurface->h - 16);
}

int Card_Intersect(Card *card, int x, int y, struct CardModel *model) 
{
  return (x >= model->x && x <= model->x + model->w &&
          y >= model->y + model->vy && y <= model->y + model->vy + model->h);
}