#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "enemy.h"
#include "level.h"
#include "screen.h"
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>

int main()
{

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("okaythespire", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  if (TTF_Init() < 0)
  {
    printf("TTF could not be initialized! SDL Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  SDL_Event e;
  int quit = 0;
  Uint32 lastTick = SDL_GetTicks();

  // fonts
  TTF_Font *font = TTF_OpenFont("res/fonts/open-sans/OpenSans-Regular.ttf", 24);

  // all the cards available in game
  Card cardOne;
  Card_Init(&cardOne, 0, ATTACK_CARD, 1, 1);
  struct CardModel cardOneModel;
  CardModel_Init(&cardOneModel);

  Card cardTwo;
  Card_Init(&cardTwo, 1, ATTACK_CARD, 2, 1);
  struct CardModel cardTwoModel;
  CardModel_Init(&cardTwoModel);

  Card cardThree;
  Card_Init(&cardThree, 2, ATTACK_CARD, 3, 2);
  struct CardModel cardThreeModel;
  CardModel_Init(&cardThreeModel);

  Card cardFour;
  Card_Init(&cardFour, 3, BLOCK_CARD, 1, 1);
  struct CardModel cardFourModel;
  CardModel_Init(&cardFourModel);

  Card cardFive;
  Card_Init(&cardFive, 4, BLOCK_CARD, 1, 3);
  struct CardModel cardFiveModel;
  CardModel_Init(&cardFiveModel);

  // init enemy (just one for now)
  Enemy enemy;
  Enemy_Init(&enemy);

  // make a deck of cards for the player
  Deck playerDeck;
  Deck_Init(&playerDeck, 1);
  Deck_AddCard(&playerDeck, &cardOne, 0);
  Deck_AddCard(&playerDeck, &cardTwo, 1);
  Deck_AddCard(&playerDeck, &cardThree, 2);
  Deck_AddCard(&playerDeck, &cardFour, 3);
  Deck_AddCard(&playerDeck, &cardFive, 4);

  Hand hand;
  Hand_Init(&hand, 5);

  Hand_AddCard(&hand, &cardOne, &cardOneModel, 0);
  Hand_AddCard(&hand, &cardTwo, &cardTwoModel, 1);
  Hand_AddCard(&hand, &cardThree, &cardThreeModel, 2);
  Hand_AddCard(&hand, &cardFour, &cardFourModel, 3);
  Hand_AddCard(&hand, &cardFive, &cardFiveModel, 4);

  // set up player
  Player player;
  Player_Init(&player, &playerDeck, &hand);

  // set up a level (i.e a fight):

  Level level;
  Level_Init(&level, &enemy, &player);

  while (!quit)
  {
    Uint32 currentTick = SDL_GetTicks();
    float deltaTime = (currentTick - lastTick) / 1000.0f; // time in seconds

    while (SDL_PollEvent(&e) != 0)
    {
      switch (e.type)
      {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT)
        {
          Level_HandleClick(&level, e.button.x, e.button.y);
        }
        break;
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          quit = 1;
          break;
        }
        break;
      }
    }

    Level_Update(&level, deltaTime);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Level_Render(renderer, &level, font);

    SDL_RenderPresent(renderer);
    lastTick = currentTick;
  }

  printf("Quitting...\n");

  Deck_Cleanup(&playerDeck);
  Hand_Cleanup(&hand);

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
