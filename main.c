#include <SDL2/SDL.h>
#include <stdio.h>
#include "card.h"

int main()
{

  int SCREEN_WIDTH = 640;
  int SCREEN_HEIGHT = 480;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("okaythespire",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN);

  if (!window)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  Card cards[2] = {
    {1, 200, 200},
    {2, 400, 200}
  };

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_Event e;
  int quit = 0;
  Uint32 lastTick = SDL_GetTicks();

  while (!quit)
  {
    Uint32 currentTick = SDL_GetTicks();
    float deltaTime = (currentTick - lastTick) / 1000.0f; // time in seconds

    // printf("Delta time: %f\n", deltaTime);

    while (SDL_PollEvent(&e) != 0)
    {
      switch(e.type)
      {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (e.button.button == SDL_BUTTON_LEFT)
          {
            // printf("Left mouse button pressed at (%d, %d)\n", e.button.x, e.button.y);

            // check if the mouse click was inside a card
            for(int i = 0; i < 2; i++) {
              if (Card_Intersect(&cards[i], e.button.x, e.button.y))
              {
                printf("Clicked on card %i!\n", cards[i].id);
              }  
            }
          }
          break;
        case SDL_KEYDOWN:
          switch(e.key.keysym.sym)
          {
            case SDLK_ESCAPE:
              quit = 1;
              break;
          }
          break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(int i = 0; i < 2; i++) {
      Card_Render(renderer, &cards[i]);
    }

    SDL_RenderPresent(renderer);

    lastTick = currentTick;
  }

  printf("Quitting...\n");
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
