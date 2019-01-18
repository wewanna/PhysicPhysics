#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
  SDL_Window *window = SDL_CreateWindow("PhsyicPhysics",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      1270, 720, SDL_WINDOW_OPENGL);

  if(nullptr == window)
    return -1;

  SDL_Event event;
  int quit = false;

  while(!quit)
  {
    while(SDL_PollEvent(&event))
    {
      if(SDL_QUIT == event.type)
        quit = true;
    }
    SDL_Delay(100);
  }

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}