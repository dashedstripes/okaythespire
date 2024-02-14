#include "card.h"
#include "deck.h"
#include "player.h"
#include "enemy.h"
#include "level.h"
#include "button.h"
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
  CardModel cardOneModel;
  CardModel_Init(&cardOneModel);
  CardModel cardTwoModel;
  CardModel_Init(&cardTwoModel);
  CardModel cardThreeModel;
  CardModel_Init(&cardThreeModel);
  CardModel cardFourModel;
  CardModel_Init(&cardFourModel);
  CardModel cardFiveModel;
  CardModel_Init(&cardFiveModel);
  
  Card cardOne;
  Card_Init(&cardOne, 0, ATTACK_CARD, 1, 1, &cardOneModel);
  Card cardTwo;
  Card_Init(&cardTwo, 1, BLOCK_CARD, 2, 1, &cardTwoModel);
  Card cardThree;
  Card_Init(&cardThree, 2, ATTACK_CARD, 3, 2, &cardThreeModel);
  Card cardFour;
  Card_Init(&cardFour, 3, BLOCK_CARD, 4, 2, &cardFourModel);
  Card cardFive;
  Card_Init(&cardFive, 4, ATTACK_CARD, 5, 3, &cardFiveModel);


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

  Button useCardButton;
  Button_Init(&useCardButton, SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 25, 100, 50, "Use Card");

  // set up player
  Player player;
  Player_Init(&player, &useCardButton);
  Player_AddCard(&player, &cardOne, 0);
  Player_AddCard(&player, &cardTwo, 1);
  Player_AddCard(&player, &cardThree, 2);
  Player_AddCard(&player, &cardFour, 3);
  Player_AddCard(&player, &cardFive, 4);

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
  Player_CleanUp(&player);

  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
