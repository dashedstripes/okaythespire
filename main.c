#include <SDL2/SDL.h>
#include <stdio.h>

int main()
{

  int SCREEN_WIDTH = 640;
  int SCREEN_HEIGHT = 480;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }

  printf("SDL initialized.\n");

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

  printf("Window created.\n");

  // Event loop
  SDL_Event e;
  int quit = 0;
  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        quit = 1;
      }
    }
    // Your rendering or update logic here


  }

  printf("Quitting...\n");
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
