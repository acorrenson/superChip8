#include <stdio.h>
#include <SDL2/SDL.h>

int main() {
  printf("Hello World\n");
  SDL_Init(SDL_INIT_VIDEO);

  /* Création de la fenêtre */
  SDL_Window* pWindow = NULL;
  SDL_Renderer* renderer;

  pWindow = SDL_CreateWindow(
    "Ma première application SDL2",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    SDL_WINDOW_SHOWN);

  if ( pWindow ) {

    printf("Successfully created an SDL2 Window \n");

    renderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;

    // main loop
    while (!quit) {
      // get event(s)
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          // handling SDL_QUIT event
          quit = 1;
        }
        
        if (e.type == SDL_KEYDOWN) {
          // handling KEYDOWN event
          quit = 1;
        }
        
        if (e.type == SDL_MOUSEBUTTONDOWN) {
          // handling MOUSECLICK event
          quit = 1;
        }
      }
    }
  } else {
    printf("Error ! \n");
  }
  
  SDL_Quit();
  return 0;
}
