#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "enemy.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main() {

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

  // all the cards available in game
  Card cardOne;
  Card_Init(&cardOne, 0, ATTACK_CARD, 1);
  Card cardTwo;
  Card_Init(&cardTwo, 1, ATTACK_CARD, 2);
  Card cardThree;
  Card_Init(&cardThree, 2, ATTACK_CARD, 3);
  Card cardFour;
  Card_Init(&cardFour, 3, BLOCK_CARD, 1);
  Card cardFive;
  Card_Init(&cardFive, 4, BLOCK_CARD, 2);

  // init player

  Player player;
  Player_Init(&player);

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
  Hand_Init(&hand, 6);

  Hand_AddCard(&hand, &cardOne, 0);
  Hand_AddCard(&hand, &cardTwo, 1);
  Hand_AddCard(&hand, &cardThree, 2);
  Hand_AddCard(&hand, &cardFour, 3);
  Hand_AddCard(&hand, &cardFive, 4);

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
          for (int i = 0; i < hand.size; i++) {
            // if (Card_Intersect(hand.cards[i], e.button.x, e.button.y, )) {
            //   printf("Card %d clicked, its type %d\n", hand.cards[i]->id, hand.cards[i]->type);
            // }
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

    Hand_Render(renderer, &hand, (SCREEN_WIDTH / 2) - (((CARD_WIDTH * 5) + (HAND_MARGIN * 4)) / 2), SCREEN_HEIGHT - CARD_HEIGHT - 20);

    SDL_RenderPresent(renderer);

    lastTick = currentTick;
  }

  printf("Quitting...\n");

  Deck_Cleanup(&playerDeck);
  Hand_Cleanup(&hand);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
