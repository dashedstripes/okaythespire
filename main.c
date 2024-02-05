#include "card.h"
#include "deck.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int main() {

  int SCREEN_WIDTH = 1280;
  int SCREEN_HEIGHT = 720;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("okaythespire", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_Event e;
  int quit = 0;
  Uint32 lastTick = SDL_GetTicks();

  Deck myDeck;
  Deck_Init(&myDeck, 6, (SCREEN_WIDTH / 2) - (((CARD_WIDTH * 5) + (DECK_MARGIN * 4)) / 2), SCREEN_HEIGHT - CARD_HEIGHT - DECK_MARGIN);

  Card cardOne;
  Card_Init(&cardOne, 0, AttackCard);
  Card cardTwo;
  Card_Init(&cardTwo, 1, AttackCard);
  Card cardThree;
  Card_Init(&cardThree, 2, AttackCard);
  Card cardFour;
  Card_Init(&cardFour, 3, BlockCard);
  Card cardFive;
  Card_Init(&cardFive, 4, BlockCard);

  Deck_AddCard(&myDeck, &cardOne, 0);
  Deck_AddCard(&myDeck, &cardTwo, 1);
  Deck_AddCard(&myDeck, &cardThree, 2);
  Deck_AddCard(&myDeck, &cardFour, 3);
  Deck_AddCard(&myDeck, &cardFive, 4);

  while (!quit) {
    Uint32 currentTick = SDL_GetTicks();
    float deltaTime = (currentTick - lastTick) / 1000.0f; // time in seconds

    // printf("Delta time: %f\n", deltaTime);

    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT) {
          // printf("Left mouse button pressed at (%d, %d)\n", e.button.x,
          // e.button.y);
          for (int i = 0; i < myDeck.size; i++) {
            if (Card_Intersect(myDeck.cards[i], e.button.x, e.button.y)) {
              printf("Card %d clicked\n", myDeck.cards[i]->id);
            }
          }
        }
        break;
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = 1;
          break;
        }
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Deck_Render(renderer, &myDeck);

    SDL_RenderPresent(renderer);

    lastTick = currentTick;
  }

  printf("Quitting...\n");

  Deck_Cleanup(&myDeck);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
