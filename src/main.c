#include <stdio.h>
#include <SDL2/SDL.h>
#include "readRom.h"

#define WIDTH 640
#define HEIGHT 320
#define SQW 10  // square width
#define SQH 10  // square height

void point(SDL_Renderer * renderer, int x, int y)
{
  // Draw a point to the screen
  SDL_Rect rect;
  rect.x = (x+1)*SQW;
  rect.y = (y+1)*SQH;
  rect.h = SQH;
  rect.w = SQW;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}

int main() {

  printf("Creating superChip8 window\n");
  SDL_Init(SDL_INIT_VIDEO);

  /* Création de la fenêtre */
  SDL_Window* pWindow = NULL;
  SDL_Renderer* renderer;

  pWindow = SDL_CreateWindow(
    "superChip8",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH + SQW,
    HEIGHT + SQH,
    SDL_WINDOW_SHOWN);

  if ( pWindow ) {
    // int a = 1;
    printf("%X\n", 0xFF << 8 | 0xFF);
    printf("Successfully created superChip8 window\n");

    renderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // draw a 0 to the screen
    point(renderer, 0, 0);
    point(renderer, 0, 1);
    point(renderer, 0, 2);
    point(renderer, 0, 3);

    point(renderer, 1, 0);
    point(renderer, 1, 3);

    point(renderer, 2, 0);
    point(renderer, 2, 1);
    point(renderer, 2, 2);
    point(renderer, 2, 3);


    readRom();

    SDL_RenderPresent(renderer);

    SDL_Event e;
    int quit = 0;

    // main loop
    while ( !quit ) {
      // get event(s)
      while ( SDL_PollEvent(&e) ) {
        if ( e.type == SDL_QUIT ) {
          // handling SDL_QUIT event
          quit = 1;
        }
        
        if ( e.type == SDL_KEYDOWN ) {
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
