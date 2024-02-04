#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{

  int SCREEN_WIDTH = 1280;
  int SCREEN_HEIGHT = 720;

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


  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_Event e;
  int quit = 0;

  int x = 200;
  int y = 150;
  int vx, vy;

  Uint32 lastTick = SDL_GetTicks(); // consider using SDL_GetTicks64 later

  while (!quit)
  {
    Uint32 currentTick = SDL_GetTicks();
    float deltaTime = currentTick - lastTick;

    while (SDL_PollEvent(&e) != 0)
    {
      switch(e.type)
      {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_KEYDOWN:
          switch(e.key.keysym.sym)
          {
            case SDLK_ESCAPE:
              quit = 1;
              break;
            case SDLK_a:
              vx = -1;
              // printf("A key pressed\n");
              break;
            case SDLK_d:
              vx = 1;
              // printf("D key pressed\n");
              break;
          }
          break;
          case SDL_KEYUP:
            switch(e.key.keysym.sym)
            {
              case SDLK_a:
                vx = 0;
                // printf("A key released\n");
              case SDLK_d:
                vx = 0;
                // printf("D key released\n");
                break;
            }
            break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {x += vx * deltaTime, y, 240, 180};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    lastTick = currentTick;
    printf("FPS: %f\n", 1000.0f / deltaTime);
  }

  printf("Quitting...\n");
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
